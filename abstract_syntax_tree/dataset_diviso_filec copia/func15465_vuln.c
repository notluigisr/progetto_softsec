TfLiteStatus Prepare(TfLiteContext* context, TfLiteNode* node) {
  static const int kOutputUniqueTensor = 0;
  static const int kOutputIndexTensor = 1;

  TF_LITE_ENSURE_EQ(context, NumInputs(node), 1);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 2);
  const TfLiteTensor* input = GetInput(context, node, 0);
  TfLiteTensor* output_unique_tensor =
      GetOutput(context, node, kOutputUniqueTensor);
  TfLiteTensor* output_index_tensor =
      GetOutput(context, node, kOutputIndexTensor);

  
  TF_LITE_ENSURE_EQ(context, NumDimensions(input), 1);
  TfLiteIntArray* output_index_shape = TfLiteIntArrayCopy(input->dims);
  
  
  SetTensorToDynamic(output_unique_tensor);
  return context->ResizeTensor(context, output_index_tensor,
                               output_index_shape);
}