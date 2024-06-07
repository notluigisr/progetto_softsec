TfLiteStatus PrepareGeneralSubOp(TfLiteContext* context,
                                 const TfLiteTensor* input_1,
                                 const TfLiteTensor* input_2,
                                 TfLiteTensor* output, TfLiteSubParams* params,
                                 OpData* op_params, int op_sign) {
  TF_LITE_ENSURE(context, output->type == kTfLiteUInt8 ||
                              output->type == kTfLiteInt8 ||
                              output->type == kTfLiteInt16);
  const auto& input1_quantization_params = input_1->params;
  const auto& input2_quantization_params = input_2->params;
  const auto& output_quantization_params = output->params;
  int32_t integer_type_min = 0;
  int32_t integer_type_max = 0;
  if (output->type == kTfLiteUInt8) {
    integer_type_min = std::numeric_limits<uint8_t>::min();
    integer_type_max = std::numeric_limits<uint8_t>::max();
  } else if (output->type == kTfLiteInt16) {
    integer_type_min = std::numeric_limits<int16_t>::min();
    integer_type_max = std::numeric_limits<int16_t>::max();
  } else {
    
    integer_type_min = std::numeric_limits<int8_t>::min();
    integer_type_max = std::numeric_limits<int8_t>::max();
  }

  TF_LITE_ENSURE(context,
                 input1_quantization_params.zero_point >= integer_type_min);
  TF_LITE_ENSURE(context,
                 input1_quantization_params.zero_point <= integer_type_max);
  TF_LITE_ENSURE(context,
                 input2_quantization_params.zero_point >= integer_type_min);
  TF_LITE_ENSURE(context,
                 input2_quantization_params.zero_point <= integer_type_max);
  TF_LITE_ENSURE(context,
                 output_quantization_params.zero_point >= integer_type_min);
  TF_LITE_ENSURE(context,
                 output_quantization_params.zero_point <= integer_type_max);

  op_params->input1_offset = -input1_quantization_params.zero_point;
  op_params->input2_offset = -input2_quantization_params.zero_point;
  op_params->output_offset = output_quantization_params.zero_point;

  
  
  
  op_params->left_shift = output->type == kTfLiteInt16 ? 15 : 20;
  const double twice_max_input_scale =
      2 * std::max(input1_quantization_params.scale,
                   input2_quantization_params.scale);
  const double real_input1_multiplier =
      input1_quantization_params.scale / twice_max_input_scale;
  const double real_input2_multiplier =
      input2_quantization_params.scale / twice_max_input_scale;
  const double real_output_multiplier =
      twice_max_input_scale /
      ((1 << op_params->left_shift) * output_quantization_params.scale);

  tflite::QuantizeMultiplierSmallerThanOneExp(real_input1_multiplier,
                                              &op_params->input1_multiplier,
                                              &op_params->input1_shift);
  tflite::QuantizeMultiplierSmallerThanOneExp(real_input2_multiplier,
                                              &op_params->input2_multiplier,
                                              &op_params->input2_shift);
  op_params->input2_multiplier *= op_sign;
  tflite::QuantizeMultiplierSmallerThanOneExp(real_output_multiplier,
                                              &op_params->output_multiplier,
                                              &op_params->output_shift);

  TF_LITE_ENSURE_STATUS(CalculateActivationRangeQuantized(
      context, params->activation, output, &op_params->output_activation_min,
      &op_params->output_activation_max));

  return kTfLiteOk;
}