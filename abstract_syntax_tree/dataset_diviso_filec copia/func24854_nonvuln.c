static void JS_RunInRestrictedContext(
    v8::FunctionCallbackInfo<v8::Value> const& args) {
  TRI_V8_TRY_CATCH_BEGIN(isolate)
  v8::HandleScope scope(isolate);

  if (args.Length() != 1 || !args[0]->IsFunction()) {
    TRI_V8_THROW_EXCEPTION_USAGE("STR");
  }

  v8::Handle<v8::Function> action = v8::Local<v8::Function>::Cast(args[0]);
  if (action.IsEmpty()) {
    THROW_ARANGO_EXCEPTION_MESSAGE(
        TRI_ERROR_INTERNAL,
        "STR");
  }

  TRI_GET_GLOBALS();

  {
    
    auto oldContext = v8g->_securityContext;

    
    v8g->_securityContext =
        JavaScriptSecurityContext::createRestrictedContext();

    
    auto guard = scopeGuard(
        [&oldContext, &v8g]() noexcept { v8g->_securityContext = oldContext; });

    v8::Handle<v8::Object> current = isolate->GetCurrentContext()->Global();
    v8::Handle<v8::Value> callArgs[] = {v8::Null(isolate)};
    v8::Handle<v8::Value> rv = action->Call(TRI_IGETC, current, 0, callArgs)
                                   .FromMaybe(v8::Local<v8::Value>());
    TRI_V8_RETURN(rv);
  }

  TRI_V8_TRY_CATCH_END
}