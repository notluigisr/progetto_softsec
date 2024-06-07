TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node) {
  OpData* data = reinterpret_cast<OpData*>(node->user_data);
  ruy::profiler::ScopeLabel label("STR");

  const TfLiteTensor* input1 = GetInput(context, node, kInputTensor1);
  const TfLiteTensor* input2 = GetInput(context, node, kInputTensor2);
  TfLiteTensor* output = GetOutput(context, node, kOutputTensor);

  if (output->type == kTfLiteFloat32) {
    EvalSquaredDifference<float>(context, node, data, input1, input2, output);
  } else if (output->type == kTfLiteInt32) {
    EvalSquaredDifference<int32_t>(context, node, data, input1, input2, output);
  } else {
    context->ReportError(
        context,
        "STR",
        output->type);
    return kTfLiteError;
  }

  return kTfLiteOk;
}