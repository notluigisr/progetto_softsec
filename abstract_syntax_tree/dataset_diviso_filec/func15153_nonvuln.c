bool ListenerImpl::rejectCxOverGlobalLimit() {
  
  Runtime::Loader* runtime = Runtime::LoaderSingleton::getExisting();

  if (runtime == nullptr) {
    
    
    
    return false;
  }

  
  
  
  
  
  const uint64_t global_cx_limit = runtime->threadsafeSnapshot()->getInteger(
      GlobalMaxCxRuntimeKey, std::numeric_limits<uint64_t>::max());
  return AcceptedSocketImpl::acceptedSocketCount() >= global_cx_limit;
}