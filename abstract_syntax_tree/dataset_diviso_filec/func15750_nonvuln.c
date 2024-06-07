MaybeLocal<Value> GetValidationErrorCode(Environment* env, int err) {
  if (err == 0)
    return Undefined(env->isolate());
  return OneByteString(env->isolate(), X509ErrorCode(err));
}