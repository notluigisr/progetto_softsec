napi_status napi_create_bigint_words(napi_env env,
                                     int sign_bit,
                                     size_t word_count,
                                     const uint64_t* words,
                                     napi_value* result) {
  NAPI_PREAMBLE(env);
  CHECK_ARG(env, words);
  CHECK_ARG(env, result);

  v8::Local<v8::Context> context = env->context();

  RETURN_STATUS_IF_FALSE(
      env, word_count <= INT_MAX, napi_invalid_arg);

  v8::MaybeLocal<v8::BigInt> b = v8::BigInt::NewFromWords(
      context, sign_bit, word_count, words);

  if (try_catch.HasCaught()) {
    return napi_set_last_error(env, napi_pending_exception);
  } else {
    CHECK_MAYBE_EMPTY(env, b, napi_generic_failure);
    *result = v8impl::JsValueFromV8LocalValue(b.ToLocalChecked());
    return napi_clear_last_error(env);
  }
}