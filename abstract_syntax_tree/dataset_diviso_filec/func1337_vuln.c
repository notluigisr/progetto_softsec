TfLiteStatus Prepare(TfLiteContext* context, TfLiteNode* node) {
  TF_LITE_ENSURE_EQ(context, NumInputs(node), 1);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);

  const TfLiteTensor* input = GetInput(context, node, kInputTensor);
  TfLiteTensor* output = GetOutput(context, node, kOutputTensor);
  output->type = kTfLiteInt32;

  
  
  
  SetTensorToPersistentRo(output);

  
  TfLiteIntArray* output_size = TfLiteIntArrayCreate(0);
  TF_LITE_ENSURE_STATUS(context->ResizeTensor(context, output, output_size));

  TF_LITE_ENSURE_EQ(context, NumDimensions(output), 0);

  
  
  if (output->type == kTfLiteInt32) {
    int32_t* output_data = GetTensorData<int32_t>(output);
    *output_data = NumDimensions(input);
  } else {
    return kTfLiteError;
  }

  return kTfLiteOk;
}