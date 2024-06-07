void StreamBase::GetFD(const FunctionCallbackInfo<Value>& args) {
  
  Base* handle;
  ASSIGN_OR_RETURN_UNWRAP(&handle,
                          args.This(),
                          args.GetReturnValue().Set(UV_EINVAL));

  StreamBase* wrap = static_cast<StreamBase*>(handle);
  if (!wrap->IsAlive())
    return args.GetReturnValue().Set(UV_EINVAL);

  args.GetReturnValue().Set(wrap->GetFD());
}