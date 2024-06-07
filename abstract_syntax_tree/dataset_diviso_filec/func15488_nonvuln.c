bool client_get(JSContext *cx, unsigned argc, Value *vp) {
  METHOD_HEADER(0)
  RootedValue clientInfo(cx, JS::GetReservedSlot(self, Slots::ClientInfo));

  if (clientInfo.isUndefined()) {
    RootedObject obj(cx, ClientInfo::create(cx));
    if (!obj)
      return false;
    clientInfo.setObject(*obj);
    JS::SetReservedSlot(self, Slots::ClientInfo, clientInfo);
  }

  args.rval().set(clientInfo);
  return true;
}