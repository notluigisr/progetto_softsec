  EventBaseAborter(EventBase* eventBase, uint32_t timeoutMS)
      : AsyncTimeout(eventBase, AsyncTimeout::InternalEnum::INTERNAL),
        eventBase_(eventBase) {
    scheduleTimeout(timeoutMS);
  }