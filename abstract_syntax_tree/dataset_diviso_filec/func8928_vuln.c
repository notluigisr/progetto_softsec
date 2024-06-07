TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node) {
  auto* params =
      reinterpret_cast<TfLiteLocalResponseNormParams*>(node->builtin_data);

  const TfLiteTensor* input = GetInput(context, node, kInputTensor);
  TfLiteTensor* output = GetOutput(context, node, kOutputTensor);

  if (output->type == kTfLiteFloat32) {

  tflite::LocalResponseNormalizationParams op_params;                \
  op_params.range = params->radius;                                  \
  op_params.bias = params->bias;                                     \
  op_params.alpha = params->alpha;                                   \
  op_params.beta = params->beta;                                     \
  type::LocalResponseNormalization(                                  \
      op_params, GetTensorShape(input), GetTensorData<float>(input), \
      GetTensorShape(output), GetTensorData<float>(output))
    if (kernel_type == kReference) {
      TF_LITE_LOCAL_RESPONSE_NORM(reference_ops);
    }
    if (kernel_type == kGenericOptimized) {
      TF_LITE_LOCAL_RESPONSE_NORM(optimized_ops);
    }
#undef TF_LITE_LOCAL_RESPONSE_NORM
  } else {
    context->ReportError(context, "STR",
                         output->type);
    return kTfLiteError;
  }

  return kTfLiteOk;
}