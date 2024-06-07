TfLiteStatus Prepare(TfLiteContext* context, TfLiteNode* node) {
  TF_LITE_ENSURE_EQ(context, NumInputs(node), 2);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);

  const TfLiteTensor* input = GetInput(context, node, kInputTensor);
  const TfLiteTensor* axis = GetInput(context, node, kAxis);
  
  TF_LITE_ENSURE_EQ(context, NumElements(axis), 1);
  
  TF_LITE_ENSURE(context,
                 axis->type == kTfLiteInt32 || axis->type == kTfLiteInt64);

  TfLiteTensor* output = GetOutput(context, node, kOutputTensor);

  auto* params = reinterpret_cast<TfLiteArgMaxParams*>(node->builtin_data);
  switch (params->output_type) {
    case kTfLiteInt32:
      output->type = kTfLiteInt32;
      break;
    case kTfLiteInt64:
      output->type = kTfLiteInt64;
      break;
    default:
      context->ReportError(context, "STR",
                           params->output_type);
      return kTfLiteError;
  }

  
  switch (input->type) {
    case kTfLiteFloat32:
    case kTfLiteUInt8:
    case kTfLiteInt8:
    case kTfLiteInt32:
      break;

    default:
      context->ReportError(
          context,
          "STR",
          input->type);
      return kTfLiteError;
  }

  TF_LITE_ENSURE(context, NumDimensions(input) >= 1);

  if (IsConstantTensor(axis)) {
    TF_LITE_ENSURE_STATUS(ResizeOutput(context, input, axis, output));
  } else {
    SetTensorToDynamic(output);
  }

  return kTfLiteOk;
}