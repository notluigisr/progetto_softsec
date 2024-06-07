TfLiteStatus ReluEval(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteTensor* input = GetInput(context, node, 0);
  TfLiteTensor* output = GetOutput(context, node, 0);
  const ReluOpData* data = reinterpret_cast<ReluOpData*>(node->user_data);
  switch (input->type) {
    case kTfLiteFloat32: {
      optimized_ops::Relu(GetTensorShape(input), GetTensorData<float>(input),
                          GetTensorShape(output), GetTensorData<float>(output));
    } break;
    
    
    case kTfLiteUInt8: {
      QuantizedReluX<uint8_t>(0.0f, std::numeric_limits<float>::infinity(),
                              input, output, data);
    } break;
    case kTfLiteInt8: {
      QuantizedReluX<int8_t>(0.0f, std::numeric_limits<float>::infinity(),
                             input, output, data);
    } break;
    default:
      TF_LITE_KERNEL_LOG(
          context, "STR",
          TfLiteTypeGetName(input->type));
      return kTfLiteError;
  }
  return kTfLiteOk;
}