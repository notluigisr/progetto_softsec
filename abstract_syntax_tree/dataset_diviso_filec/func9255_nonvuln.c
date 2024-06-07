void Subgraph::EnsureTensorsVectorCapacity() {
  const size_t required_capacity = tensors_.size() + kTensorsCapacityHeadroom;
  if (required_capacity > tensors_.capacity()) {
    
    
    
    
    size_t reserved_capacity =
        std::max(required_capacity, tensors_.capacity() * 2);
    tensors_.reserve(reserved_capacity);
    context_.tensors = tensors_.data();
  }
}