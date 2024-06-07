void inc_pending_promise_count(JSObject *self) {
  MOZ_ASSERT(is_instance(self));
  auto count = JS::GetReservedSlot(self, Slots::PendingPromiseCount).toInt32();
  count++;
  MOZ_ASSERT(count > 0);
  JS::SetReservedSlot(self, Slots::PendingPromiseCount, JS::Int32Value(count));
}