TfLiteStatus EvalQuantized(TfLiteContext* context, TfLiteNode* node,
                           OpData* data, const RuntimeShape& lhs_shape,
                           const TfLiteTensor* lhs,
                           const RuntimeShape& rhs_shape,
                           const TfLiteTensor* rhs, TfLiteTensor* output) {
  if (lhs->type == kTfLiteFloat32) {
    TfLiteTensor* input_quantized = GetTemporary(context, node, 2);
    TfLiteTensor* scaling_factors = GetTemporary(context, node, 3);
    TfLiteTensor* accum_scratch = GetTemporary(context, node, 4);
    TfLiteTensor* input_offsets = GetTemporary(context, node, 5);
    TfLiteTensor* row_sums = GetTemporary(context, node, 6);
    return EvalHybrid<kernel_type>(
        context, node, data, lhs_shape, lhs, rhs_shape, rhs, input_quantized,
        scaling_factors, accum_scratch, row_sums, input_offsets, output);
  } else if (lhs->type == kTfLiteInt8) {
    return EvalInt8<kernel_type>(context, data, lhs_shape, lhs, rhs_shape, rhs,
                                 GetTensorShape(output), output);
  } else {
    TF_LITE_KERNEL_LOG(
        context, "STR");
    return kTfLiteError;
  }
  return kTfLiteOk;
}