TfLiteStatus Prepare(TfLiteContext* context, TfLiteNode* node) {
  TF_LITE_ENSURE_EQ(context, NumInputs(node), 2);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);

  const TfLiteTensor* dims = GetInput(context, node, kDimsTensor);
  const TfLiteTensor* value = GetInput(context, node, kValueTensor);

  
  TF_LITE_ENSURE_EQ(context, NumDimensions(dims), 1);

  
  const auto dtype = dims->type;
  TF_LITE_ENSURE(context, dtype == kTfLiteInt32 || dtype == kTfLiteInt64);

  
  TF_LITE_ENSURE_EQ(context, NumDimensions(value), 0);

  TfLiteTensor* output = GetOutput(context, node, kOutputTensor);
  output->type = value->type;

  if (IsConstantTensor(dims)) {
    TF_LITE_ENSURE_OK(context, ResizeOutput(context, dims, output));
  } else {
    SetTensorToDynamic(output);
  }
  return kTfLiteOk;
}