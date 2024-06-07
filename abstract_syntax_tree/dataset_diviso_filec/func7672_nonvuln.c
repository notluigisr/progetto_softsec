void X509Certificate::ValidFrom(const FunctionCallbackInfo<Value>& args) {
  Environment* env = Environment::GetCurrent(args);
  X509Certificate* cert;
  ASSIGN_OR_RETURN_UNWRAP(&cert, args.Holder());
  BIOPointer bio(BIO_new(BIO_s_mem()));
  Local<Value> ret;
  if (GetValidFrom(env, cert->get(), bio).ToLocal(&ret))
    args.GetReturnValue().Set(ret);
}