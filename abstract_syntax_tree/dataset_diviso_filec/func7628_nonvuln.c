TfLiteStatus Subgraph::SetCustomAllocationForTensor(
    int tensor_index, const TfLiteCustomAllocation& allocation) {
  TfLiteTensor* tensor = &context_.tensors[tensor_index];
  TF_LITE_ENSURE(context(),
                 (tensor->allocation_type == kTfLiteArenaRw ||
                  tensor->allocation_type == kTfLiteArenaRwPersistent ||
                  tensor->allocation_type == kTfLiteCustom));
  TF_LITE_ENSURE_STATUS(
      ValidateCustomAllocationForTensor(context(), tensor, allocation));

  
  const auto alloc_it = std::find_if(
      custom_allocations_.begin(), custom_allocations_.end(),
      [tensor_index](
          const std::pair<int, TfLiteCustomAllocation>& existing_alloc) {
        return existing_alloc.first == tensor_index;
      });
  if (alloc_it == custom_allocations_.end()) {
    custom_allocations_.emplace_back(tensor_index, allocation);
  } else {
    alloc_it->second = allocation;
  }

  tensor->allocation_type = kTfLiteCustom;
  tensor->data.data = allocation.data;

  return kTfLiteOk;
}