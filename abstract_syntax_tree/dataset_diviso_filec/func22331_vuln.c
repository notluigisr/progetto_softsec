void OAuth2Filter::finishFlow() {

  
  
  if (found_bearer_token_) {
    if (config_->forwardBearerToken()) {
      setBearerToken(*request_headers_, access_token_);
    }
    config_->stats().oauth_success_.inc();
    decoder_callbacks_->continueDecoding();
    return;
  }

  std::string token_payload;
  if (config_->forwardBearerToken()) {
    token_payload = absl::StrCat(host_, new_expires_, access_token_, id_token_, refresh_token_);
  } else {
    token_payload = absl::StrCat(host_, new_expires_);
  }

  auto& crypto_util = Envoy::Common::Crypto::UtilitySingleton::get();

  auto token_secret = config_->tokenSecret();
  std::vector<uint8_t> token_secret_vec(token_secret.begin(), token_secret.end());
  const std::string pre_encoded_token =
      Hex::encode(crypto_util.getSha256Hmac(token_secret_vec, token_payload));
  std::string encoded_token;
  absl::Base64Escape(pre_encoded_token, &encoded_token);

  
  const std::string cookie_tail = fmt::format(CookieTailFormatString, new_expires_);
  const std::string cookie_tail_http_only =
      fmt::format(CookieTailHttpOnlyFormatString, new_expires_);

  
  
  
  
  Http::ResponseHeaderMapPtr response_headers{Http::createHeaderMap<Http::ResponseHeaderMapImpl>(
      {{Http::Headers::get().Status, std::to_string(enumToInt(Http::Code::Found))}})};

  const CookieNames& cookie_names = config_->cookieNames();

  response_headers->addReferenceKey(
      Http::Headers::get().SetCookie,
      absl::StrCat(cookie_names.oauth_hmac_, "STR", encoded_token, cookie_tail_http_only));
  response_headers->addReferenceKey(
      Http::Headers::get().SetCookie,
      absl::StrCat(cookie_names.oauth_expires_, "STR", new_expires_, cookie_tail_http_only));

  
  
  if (config_->forwardBearerToken()) {
    response_headers->addReferenceKey(
        Http::Headers::get().SetCookie,
        absl::StrCat(cookie_names.bearer_token_, "STR", access_token_, cookie_tail));
    if (id_token_ != EMPTY_STRING) {
      response_headers->addReferenceKey(Http::Headers::get().SetCookie,
                                        absl::StrCat("STR", id_token_, cookie_tail));
    }

    if (refresh_token_ != EMPTY_STRING) {
      response_headers->addReferenceKey(Http::Headers::get().SetCookie,
                                        absl::StrCat("STR", refresh_token_, cookie_tail));
    }
  }

  response_headers->setLocation(state_);

  decoder_callbacks_->encodeHeaders(std::move(response_headers), true, REDIRECT_LOGGED_IN);
  config_->stats().oauth_success_.inc();
  decoder_callbacks_->continueDecoding();
}