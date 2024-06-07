ListenerImpl::~ListenerImpl() {
  if (!workers_started_) {
    
    
    listener_init_target_.ready();
  }
}