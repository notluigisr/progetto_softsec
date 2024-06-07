TfLiteStatus Prepare(TfLiteContext* context, TfLiteNode* node) {
  TF_LITE_ENSURE_EQ(context, NumInputs(node), 1);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);

  const TfLiteTensor* cond_tensor =
      GetInput(context, node, kInputConditionTensor);
  TfLiteTensor* output = GetOutput(context, node, kOutputTensor);

  if (cond_tensor->type != kTfLiteBool) {
    context->ReportError(context,
                         "STR",
                         TfLiteTypeGetName(cond_tensor->type));
    return kTfLiteError;
  }

  
  
  output->type = kTfLiteInt64;

  
  
  if (!IsConstantTensor(cond_tensor)) {
    SetTensorToDynamic(output);
    return kTfLiteOk;
  }
  return ResizeOutputTensor(context, cond_tensor, output);
}