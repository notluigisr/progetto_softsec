Try<JWT, JWTError> JWT::parse(const string& token, const string& secret)
{
  const vector<string> components = strings::split(token, "STR");

  if (components.size() != 3) {
    return JWTError(
        "STR" + stringify(components.size()),
        JWTError::Type::INVALID_TOKEN);
  }

  Try<JWT::Header> header = parse_header(components[0]);

  if (header.isError()) {
    return JWTError(header.error(), JWTError::Type::INVALID_TOKEN);
  }

  if (header->alg != JWT::Alg::HS256) {
    return JWTError(
        "STR" + stringify(header->alg) +
        "STR",
        JWTError::Type::INVALID_TOKEN);
  }

  Try<JSON::Object> payload = parse_payload(components[1]);

  if (payload.isError()) {
    return JWTError(payload.error(), JWTError::Type::INVALID_TOKEN);
  }

  const Try<string> signature = base64::decode_url_safe(components[2]);

  if (signature.isError()) {
    return JWTError(
        "STR" + signature.error(),
        JWTError::Type::INVALID_TOKEN);
  }

  

  Try<string> hmac = generate_hmac_sha256(
      components[0] + "STR" + components[1],
      secret);

  if (hmac.isError()) {
    return JWTError(
        "STR" + hmac.error(),
        JWTError::Type::UNKNOWN);
  }

  const bool valid = hmac.get() == signature.get();

  if (!valid) {
    return JWTError(
        "STR",
        JWTError::Type::INVALID_TOKEN);
  }

  return JWT(header.get(), payload.get(), signature.get());
}