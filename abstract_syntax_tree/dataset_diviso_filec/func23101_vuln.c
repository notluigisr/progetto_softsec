TfLiteStatus Prepare(TfLiteContext* context, TfLiteNode* node) {
  TF_LITE_ENSURE_EQ(context, NumInputs(node), 3);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);

  const TfLiteTensor* start = GetInput(context, node, kStartTensor);
  const TfLiteTensor* limit = GetInput(context, node, kLimitTensor);
  const TfLiteTensor* delta = GetInput(context, node, kDeltaTensor);
  
  TF_LITE_ENSURE_EQ(context, NumDimensions(start), 0);
  TF_LITE_ENSURE_EQ(context, NumDimensions(limit), 0);
  TF_LITE_ENSURE_EQ(context, NumDimensions(delta), 0);

  
  
  const auto dtype = start->type;
  if (dtype != kTfLiteFloat32 && dtype != kTfLiteInt32) {
    context->ReportError(context, "STR",
                         TfLiteTypeGetName(dtype));
    return kTfLiteError;
  }

  TF_LITE_ENSURE_TYPES_EQ(context, limit->type, dtype);
  TF_LITE_ENSURE_TYPES_EQ(context, delta->type, dtype);

  TfLiteTensor* output = GetOutput(context, node, kOutputTensor);
  output->type = dtype;

  if (IsConstantTensor(start) && IsConstantTensor(limit) &&
      IsConstantTensor(delta)) {
    return ResizeOutput(context, start, limit, delta, output);
  }

  SetTensorToDynamic(output);
  return kTfLiteOk;
}