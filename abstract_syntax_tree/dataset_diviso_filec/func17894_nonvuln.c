ConnPoolImplBase::~ConnPoolImplBase() {
  ASSERT(isIdleImpl());
  ASSERT(connecting_stream_capacity_ == 0);
}