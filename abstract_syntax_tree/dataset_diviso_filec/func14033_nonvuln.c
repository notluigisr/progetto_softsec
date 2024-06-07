TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteTensor* input;
  TF_LITE_ENSURE_OK(context, GetInputSafe(context, node, kInputTensor, &input));
  TfLiteTensor* output;
  TF_LITE_ENSURE_OK(context,
                    GetOutputSafe(context, node, kOutputTensor, &output));
  const int num_elements = NumElements(input);
  switch (input->type) {
    case kTfLiteInt64:
      memset(GetTensorData<int64_t>(output), 0, num_elements * sizeof(int64_t));
      break;
    case kTfLiteInt32:
      memset(GetTensorData<int32_t>(output), 0, num_elements * sizeof(int32_t));
      break;
    case kTfLiteFloat32:
      memset(GetTensorData<float>(output), 0, num_elements * sizeof(float));
      break;
    default:
      context->ReportError(context,
                           "STR"
                           "STR",
                           input->type);
      return kTfLiteError;
  }
  return kTfLiteOk;
}