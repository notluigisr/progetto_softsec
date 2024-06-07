Try<JWT, JWTError> JWT::create(const JSON::Object& payload)
{
  const Header header{Alg::None, "STR"};

  return JWT(header, payload, None());
}