TfLiteStatus EvalQuantized(TfLiteContext* context, TfLiteNode* node,
                           TfLiteDivParams* params, const OpData* data,
                           const TfLiteTensor* input1,
                           const TfLiteTensor* input2, TfLiteTensor* output) {
  if (input1->type == kTfLiteUInt8 && input2->type == kTfLiteUInt8 &&
      output->type == kTfLiteUInt8) {
    tflite::ArithmeticParams op_params;
    SetActivationParams(data->output_activation_min,
                        data->output_activation_max, &op_params);
    op_params.input1_offset = -input1->params.zero_point;
    op_params.input2_offset = -input2->params.zero_point;
    op_params.output_offset = output->params.zero_point;
    op_params.output_multiplier = data->output_multiplier;
    op_params.output_shift = data->output_shift;
    bool need_broadcast = optimized_ops::ProcessBroadcastShapes(
        GetTensorShape(input1), GetTensorShape(input2), &op_params);

  type::opname(op_params, GetTensorShape(input1),                    \
               GetTensorData<dtype>(input1), GetTensorShape(input2), \
               GetTensorData<dtype>(input2), GetTensorShape(output), \
               GetTensorData<dtype>(output))
    if (kernel_type == kReference) {
      if (need_broadcast) {
        TF_LITE_DIV(reference_ops, BroadcastDivSlow, uint8_t);
      } else {
        TF_LITE_DIV(reference_ops, Div, uint8_t);
      }
    } else {
      if (need_broadcast) {
        TF_LITE_DIV(optimized_ops, BroadcastDivSlow, uint8_t);
      } else {
        TF_LITE_DIV(optimized_ops, Div, uint8_t);
      }
    }
#undef TF_LITE_DIV
  } else {
    context->ReportError(
        context, "STR");
    return kTfLiteError;
  }
  return kTfLiteOk;
}