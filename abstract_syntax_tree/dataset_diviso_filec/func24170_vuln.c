TfLiteStatus ResizeOutput(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteTensor* top_k = GetInput(context, node, kInputTopK);
  
  TF_LITE_ENSURE_TYPES_EQ(context, top_k->type, kTfLiteInt32);
  
  TF_LITE_ENSURE_EQ(context, NumElements(top_k), 1);
  const int32 k = *GetTensorData<int32_t>(top_k);

  const TfLiteTensor* input = GetInput(context, node, kInputTensor);
  const int num_dimensions = NumDimensions(input);
  
  TF_LITE_ENSURE_MSG(context, input->dims->size >= 1,
                     "STR");
  
  TF_LITE_ENSURE_MSG(context, k <= input->dims->data[num_dimensions - 1],
                     "STR");

  TfLiteIntArray* output_indexes_shape = TfLiteIntArrayCreate(num_dimensions);
  TfLiteIntArray* output_values_shape = TfLiteIntArrayCreate(num_dimensions);
  for (int i = 0; i < num_dimensions - 1; ++i) {
    output_indexes_shape->data[i] = input->dims->data[i];
    output_values_shape->data[i] = input->dims->data[i];
  }
  output_indexes_shape->data[num_dimensions - 1] = k;
  output_values_shape->data[num_dimensions - 1] = k;
  TfLiteTensor* output_indexes = GetOutput(context, node, kOutputIndexes);
  TfLiteTensor* output_values = GetOutput(context, node, kOutputValues);
  
  output_indexes->type = kTfLiteInt32;
  output_values->type = input->type;
  auto resize_tensor = [context](TfLiteTensor* tensor, TfLiteIntArray* new_size,
                                 TfLiteIntArray* delete_on_error) {
    TfLiteStatus status = context->ResizeTensor(context, tensor, new_size);
    if (status != kTfLiteOk) {
      if (delete_on_error != nullptr) {
        TfLiteIntArrayFree(delete_on_error);
      }
    }
    return status;
  };
  TF_LITE_ENSURE_OK(context, resize_tensor(output_indexes, output_indexes_shape,
                                           output_values_shape));
  TF_LITE_ENSURE_OK(context,
                    resize_tensor(output_values, output_values_shape, nullptr));
  return kTfLiteOk;
}