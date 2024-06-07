void X509Certificate::Fingerprint256(const FunctionCallbackInfo<Value>& args) {
  Environment* env = Environment::GetCurrent(args);
  X509Certificate* cert;
  ASSIGN_OR_RETURN_UNWRAP(&cert, args.Holder());
  Local<Value> ret;
  if (GetFingerprintDigest(env, EVP_sha256(), cert->get()).ToLocal(&ret))
    args.GetReturnValue().Set(ret);
}