TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteTensor* params = GetInput(context, node, kParams);
  const TfLiteTensor* indices = GetInput(context, node, kIndices);
  TfLiteTensor* output = GetOutput(context, node, kOutputTensor);

  switch (indices->type) {
    case kTfLiteInt32:
      return EvalGatherNd<int32_t>(context, params, indices, output);
    case kTfLiteInt64:
      return EvalGatherNd<int64_t>(context, params, indices, output);
    default:
      context->ReportError(
          context, "STR",
          TfLiteTypeGetName(indices->type));
      return kTfLiteError;
  }
}