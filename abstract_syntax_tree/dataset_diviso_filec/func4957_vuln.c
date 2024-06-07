TfLiteStatus Prepare(TfLiteContext* context, TfLiteNode* node) {
  TF_LITE_ENSURE_EQ(context, NumInputs(node), 2);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);

  
  const TfLiteTensor* input = GetInput(context, node, kInputTensor);
  TF_LITE_ENSURE(context, NumDimensions(input) >= 2);
  if (input->type != kTfLiteFloat32) {
    context->ReportError(context,
                         "STR",
                         TfLiteTypeGetName(input->type));
    return kTfLiteError;
  }

  
  const TfLiteTensor* fft_length = GetInput(context, node, kFftLengthTensor);
  const RuntimeShape fft_length_shape = GetTensorShape(fft_length);

  TF_LITE_ENSURE_EQ(context, NumDimensions(fft_length), 1);
  TF_LITE_ENSURE_EQ(context, fft_length_shape.Dims(0), 2);
  if (fft_length->type != kTfLiteInt32) {
    context->ReportError(context,
                         "STR",
                         TfLiteTypeGetName(fft_length->type));
    return kTfLiteError;
  }

  
  TF_LITE_ENSURE_STATUS(InitTemporaryTensors(context, node));

  
  TfLiteTensor* output = GetOutput(context, node, kOutputTensor);
  output->type = kTfLiteComplex64;

  
  
  
  if (!IsConstantTensor(fft_length)) {
    TfLiteTensor* fft_integer_working_area =
        GetTemporary(context, node, kFftIntegerWorkingAreaTensor);
    TfLiteTensor* fft_double_working_area =
        GetTemporary(context, node, kFftDoubleWorkingAreaTensor);
    SetTensorToDynamic(fft_integer_working_area);
    SetTensorToDynamic(fft_double_working_area);
    SetTensorToDynamic(output);
    return kTfLiteOk;
  }

  TF_LITE_ENSURE_STATUS(ResizeOutputandTemporaryTensors(context, node));
  return kTfLiteOk;
}