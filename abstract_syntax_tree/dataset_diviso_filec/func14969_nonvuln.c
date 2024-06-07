napi_status napi_get_array_length(napi_env env,
                                  napi_value value,
                                  uint32_t* result) {
  NAPI_PREAMBLE(env);
  CHECK_ARG(env, value);
  CHECK_ARG(env, result);

  v8::Local<v8::Value> val = v8impl::V8LocalValueFromJsValue(value);
  RETURN_STATUS_IF_FALSE(env, val->IsArray(), napi_array_expected);

  v8::Local<v8::Array> arr = val.As<v8::Array>();
  *result = arr->Length();

  return GET_RETURN_STATUS(env);
}