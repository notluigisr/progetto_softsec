  CallbackWrapper(napi_value this_arg, size_t args_length, void* data)
      : _this(this_arg), _args_length(args_length), _data(data) {}