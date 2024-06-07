JSString *status_message(JSObject *obj) {
  MOZ_ASSERT(is_instance(obj));
  return JS::GetReservedSlot(obj, Slots::StatusMessage).toString();
}