void TRI_InitV8ServerUtils(v8::Isolate* isolate) {
  TRI_AddGlobalFunctionVocbase(
      isolate, TRI_V8_ASCII_STRING(isolate, "STR"),
      JS_ClusterApiJwtPolicy, true);
  TRI_AddGlobalFunctionVocbase(
      isolate, TRI_V8_ASCII_STRING(isolate, "STR"),
      JS_IsFoxxApiDisabled, true);
  TRI_AddGlobalFunctionVocbase(
      isolate, TRI_V8_ASCII_STRING(isolate, "STR"),
      JS_IsFoxxStoreDisabled, true);
  TRI_AddGlobalFunctionVocbase(
      isolate, TRI_V8_ASCII_STRING(isolate, "STR"),
      JS_RunInRestrictedContext, true);

  TRI_AddGlobalFunctionVocbase(
      isolate, TRI_V8_ASCII_STRING(isolate, "STR"),
      JS_CreateHotbackup);

  
  TRI_AddGlobalFunctionVocbase(
      isolate, TRI_V8_ASCII_STRING(isolate, "STR"),
      JS_DebugClearFailAt);

#ifdef ARANGODB_ENABLE_FAILURE_TESTS
  TRI_AddGlobalFunctionVocbase(
      isolate, TRI_V8_ASCII_STRING(isolate, "STR"),
      JS_DebugTerminate);
  TRI_AddGlobalFunctionVocbase(
      isolate, TRI_V8_ASCII_STRING(isolate, "STR"),
      JS_DebugSetFailAt);
  TRI_AddGlobalFunctionVocbase(
      isolate, TRI_V8_ASCII_STRING(isolate, "STR"),
      JS_DebugRemoveFailAt);
  TRI_AddGlobalFunctionVocbase(
      isolate, TRI_V8_ASCII_STRING(isolate, "STR"),
      JS_DebugShouldFailAt);
#endif

  
  TRI_GET_GLOBALS();
  FoxxFeature& foxxFeature = v8g->_server.getFeature<FoxxFeature>();

  isolate->GetCurrentContext()
      ->Global()
      ->DefineOwnProperty(
          TRI_IGETC, TRI_V8_ASCII_STRING(isolate, "STR"),
          v8::Number::New(isolate, foxxFeature.pollInterval()), v8::ReadOnly)
      .FromMaybe(false);  

  isolate->GetCurrentContext()
      ->Global()
      ->DefineOwnProperty(
          TRI_IGETC,
          TRI_V8_ASCII_STRING(isolate, "STR"),
          v8::Boolean::New(isolate, foxxFeature.startupWaitForSelfHeal()),
          v8::ReadOnly)
      .FromMaybe(false);  
}