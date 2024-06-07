RequestHandle request_handle(JSObject *obj) {
  return RequestHandle{static_cast<uint32_t>(JS::GetReservedSlot(obj, Slots::Request).toInt32())};
}