MaybeLocal<Value> GetValidationErrorReason(Environment* env, int err) {
  if (err == 0)
    return Undefined(env->isolate());
  const char* reason = X509_verify_cert_error_string(err);
  return OneByteString(env->isolate(), reason);
}