TfLiteStatus ResizeOutput(TfLiteContext* context, const TfLiteTensor* input,
                          const TfLiteTensor* axis, TfLiteTensor* output) {
  int axis_value;
  
  if (axis->type == kTfLiteInt64) {
    axis_value = static_cast<int>(*GetTensorData<int64_t>(axis));
  } else {
    axis_value = *GetTensorData<int>(axis);
  }
  if (axis_value < 0) {
    axis_value += NumDimensions(input);
  }

  
  TfLiteIntArray* output_dims = TfLiteIntArrayCreate(NumDimensions(input) - 1);
  int j = 0;
  for (int i = 0; i < NumDimensions(input); ++i) {
    if (i != axis_value) {
      output_dims->data[j] = SizeOfDimension(input, i);
      ++j;
    }
  }
  return context->ResizeTensor(context, output, output_dims);
}