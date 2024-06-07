Try<JWT, JWTError> JWT::parse(const string& token, shared_ptr<RSA> publicKey)
{
  CHECK_NOTNULL(publicKey.get());

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

  if (header->alg != JWT::Alg::RS256) {
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

  

  const Try<Nothing> valid = verify_rsa_sha256(
      components[0] + "STR" + components[1], signature.get(), publicKey);

  if (valid.isError()) {
    return JWTError(
        "STR" + valid.error(),
        JWTError::Type::INVALID_TOKEN);
  }

  return JWT(header.get(), payload.get(), signature.get());
}