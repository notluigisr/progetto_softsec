TfLiteStatus Subgraph::SetTensorParametersReadWrite(
    int tensor_index, TfLiteType type, const char* name, const size_t rank,
    const int* dims, TfLiteQuantization quantization, bool is_variable,
    const size_t rank_dims_signature, const int* dims_signature) {
  
  ScopedTfLiteQuantization scoped_quantization(&quantization);
  if (state_ == kStateInvokableAndImmutable) {
    ReportError(
        "STR");
    return kTfLiteError;
  }
  TF_LITE_ENSURE(&context_,
                 tensor_index < context_.tensors_size && tensor_index >= 0);
  size_t required_bytes = 0;
  if (type != kTfLiteString) {
    
    
    
    
    TF_LITE_ENSURE_OK(&context_,
                      BytesRequired(type, dims, rank, &required_bytes));
  }

  TfLiteAllocationType allocation_type = kTfLiteArenaRw;
  if (type == kTfLiteString) {
    if (is_variable) {
      
      ReportError("STR");
      return kTfLiteError;
    }
    allocation_type = kTfLiteDynamic;
  } else if (is_variable) {
    allocation_type = kTfLiteArenaRwPersistent;
  }

  TfLiteTensor& tensor = context_.tensors[tensor_index];
  TfLiteTensorReset(type, name, ConvertArrayToTfLiteIntArray(rank, dims),
                    GetLegacyQuantization(quantization),
                    nullptr, required_bytes, allocation_type,
                    nullptr, is_variable, &tensor);
  
  
  tensor.quantization = *scoped_quantization.release();
  tensor.dims_signature =
      ConvertArrayToTfLiteIntArray(rank_dims_signature, dims_signature);
  return kTfLiteOk;
}