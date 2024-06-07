TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteTensor* input = GetInput(context, node, kInputTensor);
  TfLiteTensor* output = GetOutput(context, node, kOutputTensor);

  
  
  
  if (IsDynamicTensor(output)) {
    TF_LITE_ENSURE_OK(context, ResizeOutput(context, node));
  }

  
  
  
  
  
  
  if (output->type == kTfLiteString) {
    auto bytes_required = input->bytes;
    TfLiteTensorRealloc(bytes_required, output);
    output->bytes = bytes_required;
  }

  memcpy(output->data.raw, input->data.raw, input->bytes);

  return kTfLiteOk;
}