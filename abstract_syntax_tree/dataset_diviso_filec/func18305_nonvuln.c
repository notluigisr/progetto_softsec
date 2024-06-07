napi_status napi_get_typedarray_info(napi_env env,
                                     napi_value typedarray,
                                     napi_typedarray_type* type,
                                     size_t* length,
                                     void** data,
                                     napi_value* arraybuffer,
                                     size_t* byte_offset) {
  CHECK_ENV(env);
  CHECK_ARG(env, typedarray);

  v8::Local<v8::Value> value = v8impl::V8LocalValueFromJsValue(typedarray);
  RETURN_STATUS_IF_FALSE(env, value->IsTypedArray(), napi_invalid_arg);

  v8::Local<v8::TypedArray> array = value.As<v8::TypedArray>();

  if (type != nullptr) {
    if (value->IsInt8Array()) {
      *type = napi_int8_array;
    } else if (value->IsUint8Array()) {
      *type = napi_uint8_array;
    } else if (value->IsUint8ClampedArray()) {
      *type = napi_uint8_clamped_array;
    } else if (value->IsInt16Array()) {
      *type = napi_int16_array;
    } else if (value->IsUint16Array()) {
      *type = napi_uint16_array;
    } else if (value->IsInt32Array()) {
      *type = napi_int32_array;
    } else if (value->IsUint32Array()) {
      *type = napi_uint32_array;
    } else if (value->IsFloat32Array()) {
      *type = napi_float32_array;
    } else if (value->IsFloat64Array()) {
      *type = napi_float64_array;
    } else if (value->IsBigInt64Array()) {
      *type = napi_bigint64_array;
    } else if (value->IsBigUint64Array()) {
      *type = napi_biguint64_array;
    }
  }

  if (length != nullptr) {
    *length = array->Length();
  }

  v8::Local<v8::ArrayBuffer> buffer;
  if (data != nullptr || arraybuffer != nullptr) {
    
    
    buffer = array->Buffer();
  }

  if (data != nullptr) {
    *data = static_cast<uint8_t*>(buffer->GetBackingStore()->Data()) +
            array->ByteOffset();
  }

  if (arraybuffer != nullptr) {
    *arraybuffer = v8impl::JsValueFromV8LocalValue(buffer);
  }

  if (byte_offset != nullptr) {
    *byte_offset = array->ByteOffset();
  }

  return napi_clear_last_error(env);
}