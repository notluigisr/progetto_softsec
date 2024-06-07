napi_value Init(napi_env env, napi_value exports) {
  napi_property_descriptor properties[] = {
    DECLARE_NAPI_PROPERTY("STR", TestLatin1),
    DECLARE_NAPI_PROPERTY("STR", TestLatin1Insufficient),
    DECLARE_NAPI_PROPERTY("STR", TestUtf8),
    DECLARE_NAPI_PROPERTY("STR", TestUtf8Insufficient),
    DECLARE_NAPI_PROPERTY("STR", TestUtf16),
    DECLARE_NAPI_PROPERTY("STR", TestUtf16Insufficient),
    DECLARE_NAPI_PROPERTY("STR", Utf16Length),
    DECLARE_NAPI_PROPERTY("STR", Utf8Length),
    DECLARE_NAPI_PROPERTY("STR", TestLargeUtf8),
    DECLARE_NAPI_PROPERTY("STR", TestLargeLatin1),
    DECLARE_NAPI_PROPERTY("STR", TestLargeUtf16),
  };

  NAPI_CALL(env, napi_define_properties(
      env, exports, sizeof(properties) / sizeof(*properties), properties));

  return exports;
}