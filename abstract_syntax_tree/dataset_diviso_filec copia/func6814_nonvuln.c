void DequantizeClassPredictions(const TfLiteTensor* input_class_predictions,
                                const int num_boxes,
                                const int num_classes_with_background,
                                TfLiteTensor* scores) {
  float quant_zero_point =
      static_cast<float>(input_class_predictions->params.zero_point);
  float quant_scale = static_cast<float>(input_class_predictions->params.scale);
  Dequantizer dequantize(quant_zero_point, quant_scale);
  const uint8* scores_quant = GetTensorData<uint8>(input_class_predictions);
  for (int idx = 0; idx < num_boxes * num_classes_with_background; ++idx) {
    GetTensorData<float>(scores)[idx] = dequantize(scores_quant[idx]);
  }
}