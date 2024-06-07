void Subgraph::SetCancellationFunction(void* data,
                                       bool (*check_cancelled_func)(void*)) {
  cancellation_data_ = data;
  check_cancelled_func_ = check_cancelled_func;
}