TfLiteStatus EvalImpl(TfLiteContext* context, const TfLiteTensor* input,
                      TfLiteNode* node) {
  auto* params = reinterpret_cast<TfLiteUniqueParams*>(node->builtin_data);
  if (params == nullptr) {
    context->ReportError(context, "STR");
    return kTfLiteError;
  }
  switch (params->index_out_type) {
    case kTfLiteInt32:
      return EvalImpl<T, int32_t>(context, input, node);
    case kTfLiteInt64:
      return EvalImpl<T, int64_t>(context, input, node);
    default:
      context->ReportError(
          context,
          "STR",
          TfLiteTypeGetName(params->index_out_type));
  }
  return kTfLiteError;
}