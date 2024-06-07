void X509Certificate::CheckIssued(const FunctionCallbackInfo<Value>& args) {
  Environment* env = Environment::GetCurrent(args);
  X509Certificate* cert;
  ASSIGN_OR_RETURN_UNWRAP(&cert, args.Holder());

  CHECK(args[0]->IsObject());
  CHECK(X509Certificate::HasInstance(env, args[0].As<Object>()));

  X509Certificate* issuer;
  ASSIGN_OR_RETURN_UNWRAP(&issuer, args[0]);

  args.GetReturnValue().Set(
    X509_check_issued(issuer->get(), cert->get()) == X509_V_OK);
}