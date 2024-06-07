TfLiteStatus ResizeOutput(TfLiteContext* context, TfLiteNode* node) {
  TfLiteIntArray* output_shape = GetOutputShape(context, node);
  std::unique_ptr<TfLiteIntArray, void (*)(TfLiteIntArray*)>
      scoped_output_shape(output_shape, TfLiteIntArrayFree);

  const TfLiteTensor* input = GetInput(context, node, kInputTensor);
  TfLiteTensor* output = GetOutput(context, node, kOutputTensor);

  
  
  
  
  int num_input_elements = NumElements(input);

  int num_output_elements = 1;
  int stretch_dim = -1;
  for (int i = 0; i < output_shape->size; ++i) {
    int value = output_shape->data[i];
    if (value == -1) {
      TF_LITE_ENSURE_EQ(context, stretch_dim, -1);
      stretch_dim = i;
    } else {
      num_output_elements *= value;
    }
  }
  if (stretch_dim != -1) {
    output_shape->data[stretch_dim] = num_input_elements / num_output_elements;
    num_output_elements *= output_shape->data[stretch_dim];
  }

  TF_LITE_ENSURE_EQ(context, num_input_elements, num_output_elements);
  return context->ResizeTensor(context, output, scoped_output_shape.release());
}