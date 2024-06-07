napi_status napi_create_reference(napi_env env,
                                  napi_value value,
                                  uint32_t initial_refcount,
                                  napi_ref* result) {
  
  
  CHECK_ENV(env);
  CHECK_ARG(env, value);
  CHECK_ARG(env, result);

  v8::Local<v8::Value> v8_value = v8impl::V8LocalValueFromJsValue(value);

  if (!(v8_value->IsObject() || v8_value->IsFunction())) {
    return napi_set_last_error(env, napi_object_expected);
  }

  v8impl::Reference* reference =
      v8impl::Reference::New(env, v8_value, initial_refcount, false);

  *result = reinterpret_cast<napi_ref>(reference);
  return napi_clear_last_error(env);
}