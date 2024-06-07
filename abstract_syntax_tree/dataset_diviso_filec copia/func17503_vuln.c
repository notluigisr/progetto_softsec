TfLiteStatus ReverseSequenceHelper(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteTensor* seq_lengths_tensor =
      GetInput(context, node, kSeqLengthsTensor);
  switch (seq_lengths_tensor->type) {
    case kTfLiteInt32: {
      return ReverseSequenceImpl<T, int32_t>(context, node);
    }
    case kTfLiteInt64: {
      return ReverseSequenceImpl<T, int64_t>(context, node);
    }
    default: {
      context->ReportError(
          context,
          "STR",
          TfLiteTypeGetName(seq_lengths_tensor->type));
      return kTfLiteError;
    }
  }
  return kTfLiteOk;
}