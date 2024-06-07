Filter::~Filter() {
  
  ASSERT(upstream_requests_.empty());
  ASSERT(!retry_state_);
}