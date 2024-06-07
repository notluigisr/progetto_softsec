TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node) {
  OpData* op_data = reinterpret_cast<OpData*>(node->user_data);
  OpContext op_context(context, node);
  if (IsConstantTensor(op_context.input) && op_data->float_input_initialized) {
    return kTfLiteOk;
  }

  
  TfLiteTensor* dequantized = GetTemporary(context, node, 0);
  auto status = builtin::dequantize::DequantizeImpl<kernel_type>(
      context, node, op_context.input, dequantized);
  if (status != kTfLiteOk) {
    return status;
  }

  if (IsConstantTensor(op_context.input)) {
    op_data->float_input_initialized = true;
  }

  
  if (op_data->tolerance < 0.1) {
    std::vector<double> diffs, temp;
    diffs.reserve(NumElements(dequantized));
    temp.reserve(NumElements(dequantized));
    for (int i = 0; i < NumElements(op_context.ref); ++i) {
      float dequant = GetTensorData<float>(dequantized)[i];
      float reference = GetTensorData<float>(op_context.ref)[i];
      diffs.push_back(dequant - reference);
    }
    double mean =
        std::accumulate(diffs.begin(), diffs.end(), 0.0) / diffs.size();
    double max_diff = 0.0;
    std::transform(diffs.begin(), diffs.end(), temp.begin(),
                   [mean, &max_diff](double x) {
                     max_diff = std::max(max_diff, std::abs(x));
                     return x - mean;
                   });
    double sq_sum =
        std::inner_product(temp.begin(), temp.end(), temp.begin(), 0.0);
    double std = std::sqrt(sq_sum / diffs.size());
    TF_LITE_KERNEL_LOG(
        context,
        "STR", std,
        mean, max_diff, op_context.input->params.scale,
        op_context.input->params.zero_point);
    return kTfLiteOk;
  }

  
  auto max_diff = op_data->tolerance * op_context.input->params.scale;
  for (int i = 0; i < NumElements(op_context.ref); ++i) {
    int32_t value = GetQuantizedValue(op_context, i);
    float dequant = GetTensorData<float>(dequantized)[i];
    float reference = GetTensorData<float>(op_context.ref)[i];
    float diff = std::abs(reference - dequant);
    if (diff > max_diff) {
      TF_LITE_KERNEL_LOG(
          context,
          "STR"
          "STR",
          reference, value, op_context.input->params.scale,
          op_context.input->params.zero_point, reference, dequant, diff,
          max_diff, op_data->tolerance);
      return kTfLiteError;
    }
  }
  return kTfLiteOk;
}