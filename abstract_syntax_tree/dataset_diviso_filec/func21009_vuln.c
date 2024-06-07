TfLiteStatus ResizeOutputandTemporaryTensors(TfLiteContext* context,
                                             TfLiteNode* node) {
  const TfLiteTensor* input = GetInput(context, node, kInputTensor);
  const int num_dims = NumDimensions(input);
  TF_LITE_ENSURE(context, num_dims >= 2);
  const TfLiteTensor* fft_length = GetInput(context, node, kFftLengthTensor);
  const int32_t* fft_length_data = GetTensorData<int32_t>(fft_length);
  
  TF_LITE_ENSURE(context, IsPowerOfTwo(fft_length_data[0]));
  TF_LITE_ENSURE(context, IsPowerOfTwo(fft_length_data[1]));

  int fft_height, fft_width;
  fft_height = fft_length_data[0];
  fft_width = fft_length_data[1];
  int fft_working_length = std::max(fft_height, fft_width / 2);
  int half_fft_working_length = fft_working_length / 2;

  
  TfLiteTensor* output = GetOutput(context, node, kOutputTensor);
  TfLiteIntArray* output_shape = TfLiteIntArrayCopy(input->dims);
  output_shape->data[num_dims - 2] = fft_length_data[0];
  output_shape->data[num_dims - 1] = fft_length_data[1] / 2 + 1;
  TF_LITE_ENSURE_STATUS(context->ResizeTensor(context, output, output_shape));

  
  TfLiteTensor* fft_integer_working_area =
      GetTemporary(context, node, kFftIntegerWorkingAreaTensor);
  TfLiteIntArray* fft_integer_working_area_shape = TfLiteIntArrayCreate(1);
  fft_integer_working_area_shape->data[0] =
      2 + static_cast<int>(sqrt(fft_working_length));
  TF_LITE_ENSURE_STATUS(context->ResizeTensor(context, fft_integer_working_area,
                                              fft_integer_working_area_shape));

  
  TfLiteTensor* fft_double_working_area =
      GetTemporary(context, node, kFftDoubleWorkingAreaTensor);
  TfLiteIntArray* fft_double_working_area_shape = TfLiteIntArrayCreate(1);
  fft_double_working_area_shape->data[0] =
      half_fft_working_length + fft_width / 4;
  TF_LITE_ENSURE_STATUS(context->ResizeTensor(context, fft_double_working_area,
                                              fft_double_working_area_shape));

  return kTfLiteOk;
}