bool is_int_typed_array(JSObject *obj) {
  return JS_IsInt8Array(obj) || JS_IsUint8Array(obj) || JS_IsInt16Array(obj) ||
         JS_IsUint16Array(obj) || JS_IsInt32Array(obj) || JS_IsUint32Array(obj) ||
         JS_IsUint8ClampedArray(obj) || JS_IsBigInt64Array(obj) || JS_IsBigUint64Array(obj);
}