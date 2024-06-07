void EvalDiv(TfLiteContext* context, TfLiteNode* node, TfLiteDivParams* params,
             const OpData* data, const TfLiteTensor* input1,
             const TfLiteTensor* input2, TfLiteTensor* output) {

  tflite::ArithmeticParams op_params;                                    \
  data_type output_activation_min, output_activation_max;                \
  CalculateActivationRange(params->activation, &output_activation_min,   \
                           &output_activation_max);                      \
  SetActivationParams(output_activation_min, output_activation_max,      \
                      &op_params);                                       \
  type::opname(op_params, GetTensorShape(input1),                        \
               GetTensorData<data_type>(input1), GetTensorShape(input2), \
               GetTensorData<data_type>(input2), GetTensorShape(output), \
               GetTensorData<data_type>(output))
  if (output->type == kTfLiteInt32) {
    if (kernel_type == kReference) {
      if (data->requires_broadcast) {
        TF_LITE_DIV(reference_ops, BroadcastDivSlow, int32_t);
      } else {
        TF_LITE_DIV(reference_ops, Div, int32_t);
      }
    } else {
      if (data->requires_broadcast) {
        TF_LITE_DIV(optimized_ops, BroadcastDivSlow, int32_t);
      } else {
        TF_LITE_DIV(optimized_ops, Div, int32_t);
      }
    }
  } else if (output->type == kTfLiteFloat32) {
    if (kernel_type == kReference) {
      if (data->requires_broadcast) {
        TF_LITE_DIV(reference_ops, BroadcastDivSlow, float);
      } else {
        TF_LITE_DIV(reference_ops, Div, float);
      }
    } else {
      if (data->requires_broadcast) {
        TF_LITE_DIV(optimized_ops, BroadcastDivSlow, float);
      } else {
        TF_LITE_DIV(optimized_ops, Div, float);
      }
    }
  }
#undef TF_LITE_DIV
}