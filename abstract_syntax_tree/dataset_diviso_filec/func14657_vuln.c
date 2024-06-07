TfLiteStatus Prepare(TfLiteContext* context, TfLiteNode* node) {
  TF_LITE_ENSURE(context, NumInputs(node) == 1 || NumInputs(node) == 2);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);

  
  
  
  
  TfLiteTensor* output = GetOutput(context, node, kOutputTensor);
  if (output->type != kTfLiteString) {
    if (NumInputs(node) == 1 ||
        IsConstantTensor(GetInput(context, node, kShapeTensor))) {
      TF_LITE_ENSURE_OK(context, ResizeOutput(context, node));
    } else {
      SetTensorToDynamic(output);
    }
  }
  return kTfLiteOk;
}