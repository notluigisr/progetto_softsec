static bool IsAllocationInlineable(Handle<JSFunction> constructor) {
  return constructor->has_initial_map() &&
      constructor->initial_map()->instance_type() == JS_OBJECT_TYPE &&
      constructor->initial_map()->instance_size() < HAllocateObject::kMaxSize;
}