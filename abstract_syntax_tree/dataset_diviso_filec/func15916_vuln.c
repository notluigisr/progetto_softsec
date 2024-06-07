void InitializeHttpParser(Local<Object> target,
                          Local<Value> unused,
                          Local<Context> context,
                          void* priv) {
  Environment* env = Environment::GetCurrent(context);
  BindingData* const binding_data =
      env->AddBindingData<BindingData>(context, target);
  if (binding_data == nullptr) return;

  Local<FunctionTemplate> t = env->NewFunctionTemplate(Parser::New);
  t->InstanceTemplate()->SetInternalFieldCount(Parser::kInternalFieldCount);
  t->SetClassName(FIXED_ONE_BYTE_STRING(env->isolate(), "STR"));

  t->Set(FIXED_ONE_BYTE_STRING(env->isolate(), "STR"),
         Integer::New(env->isolate(), HTTP_REQUEST));
  t->Set(FIXED_ONE_BYTE_STRING(env->isolate(), "STR"),
         Integer::New(env->isolate(), HTTP_RESPONSE));
  t->Set(FIXED_ONE_BYTE_STRING(env->isolate(), "STR"),
         Integer::NewFromUnsigned(env->isolate(), kOnHeaders));
  t->Set(FIXED_ONE_BYTE_STRING(env->isolate(), "STR"),
         Integer::NewFromUnsigned(env->isolate(), kOnHeadersComplete));
  t->Set(FIXED_ONE_BYTE_STRING(env->isolate(), "STR"),
         Integer::NewFromUnsigned(env->isolate(), kOnBody));
  t->Set(FIXED_ONE_BYTE_STRING(env->isolate(), "STR"),
         Integer::NewFromUnsigned(env->isolate(), kOnMessageComplete));
  t->Set(FIXED_ONE_BYTE_STRING(env->isolate(), "STR"),
         Integer::NewFromUnsigned(env->isolate(), kOnExecute));
  t->Set(FIXED_ONE_BYTE_STRING(env->isolate(), "STR"),
         Integer::NewFromUnsigned(env->isolate(), kOnTimeout));

  Local<Array> methods = Array::New(env->isolate());

    methods->Set(env->context(),                                              \
        num, FIXED_ONE_BYTE_STRING(env->isolate(), #string)).Check();
  HTTP_METHOD_MAP(V)
#undef V
  target->Set(env->context(),
              FIXED_ONE_BYTE_STRING(env->isolate(), "STR"),
              methods).Check();

  t->Inherit(AsyncWrap::GetConstructorTemplate(env));
  env->SetProtoMethod(t, "STR", Parser::Close);
  env->SetProtoMethod(t, "STR", Parser::Free);
  env->SetProtoMethod(t, "STR", Parser::Execute);
  env->SetProtoMethod(t, "STR", Parser::Finish);
  env->SetProtoMethod(t, "STR", Parser::Initialize);
  env->SetProtoMethod(t, "STR", Parser::Pause<true>);
  env->SetProtoMethod(t, "STR", Parser::Pause<false>);
  env->SetProtoMethod(t, "STR", Parser::Consume);
  env->SetProtoMethod(t, "STR", Parser::Unconsume);
  env->SetProtoMethod(t, "STR", Parser::GetCurrentBuffer);

  target->Set(env->context(),
              FIXED_ONE_BYTE_STRING(env->isolate(), "STR"),
              t->GetFunction(env->context()).ToLocalChecked()).Check();
}