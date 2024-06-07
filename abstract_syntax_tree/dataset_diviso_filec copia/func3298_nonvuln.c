napi_status napi_get_cb_info(
    napi_env env,               
    napi_callback_info cbinfo,  
    size_t* argc,      
                       
    napi_value* argv,  
    napi_value* this_arg,  
    void** data) {         
  CHECK_ENV(env);
  CHECK_ARG(env, cbinfo);

  v8impl::CallbackWrapper* info =
      reinterpret_cast<v8impl::CallbackWrapper*>(cbinfo);

  if (argv != nullptr) {
    CHECK_ARG(env, argc);
    info->Args(argv, *argc);
  }
  if (argc != nullptr) {
    *argc = info->ArgsLength();
  }
  if (this_arg != nullptr) {
    *this_arg = info->This();
  }
  if (data != nullptr) {
    *data = info->Data();
  }

  return napi_clear_last_error(env);
}