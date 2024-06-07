TfLiteStatus NonMaxSuppressionMultiClassFastHelper(TfLiteContext* context,
                                                   TfLiteNode* node,
                                                   OpData* op_data,
                                                   const float* scores) {
  const TfLiteTensor* input_box_encodings =
      GetInput(context, node, kInputTensorBoxEncodings);
  const TfLiteTensor* input_class_predictions =
      GetInput(context, node, kInputTensorClassPredictions);
  const TfLiteTensor* decoded_boxes =
      &context->tensors[op_data->decoded_boxes_index];

  TfLiteTensor* detection_boxes =
      GetOutput(context, node, kOutputTensorDetectionBoxes);
  TfLiteTensor* detection_classes =
      GetOutput(context, node, kOutputTensorDetectionClasses);
  TfLiteTensor* detection_scores =
      GetOutput(context, node, kOutputTensorDetectionScores);
  TfLiteTensor* num_detections =
      GetOutput(context, node, kOutputTensorNumDetections);

  const int num_boxes = input_box_encodings->dims->data[1];
  const int num_classes = op_data->num_classes;
  const int max_categories_per_anchor = op_data->max_classes_per_detection;
  const int num_classes_with_background =
      input_class_predictions->dims->data[2];
  
  int label_offset = num_classes_with_background - num_classes;
  TF_LITE_ENSURE(context, (max_categories_per_anchor > 0));
  const int num_categories_per_anchor =
      std::min(max_categories_per_anchor, num_classes);
  std::vector<float> max_scores;
  max_scores.resize(num_boxes);
  std::vector<int> sorted_class_indices;
  sorted_class_indices.resize(num_boxes * num_classes);
  for (int row = 0; row < num_boxes; row++) {
    const float* box_scores =
        scores + row * num_classes_with_background + label_offset;
    int* class_indices = sorted_class_indices.data() + row * num_classes;
    DecreasingPartialArgSort(box_scores, num_classes, num_categories_per_anchor,
                             class_indices);
    max_scores[row] = box_scores[class_indices[0]];
  }
  
  std::vector<int> selected;
  TF_LITE_ENSURE_STATUS(NonMaxSuppressionSingleClassHelper(
      context, node, op_data, max_scores, &selected, op_data->max_detections));
  
  int output_box_index = 0;
  for (const auto& selected_index : selected) {
    const float* box_scores =
        scores + selected_index * num_classes_with_background + label_offset;
    const int* class_indices =
        sorted_class_indices.data() + selected_index * num_classes;

    for (int col = 0; col < num_categories_per_anchor; ++col) {
      int box_offset = num_categories_per_anchor * output_box_index + col;
      
      ReInterpretTensor<BoxCornerEncoding*>(detection_boxes)[box_offset] =
          ReInterpretTensor<const BoxCornerEncoding*>(
              decoded_boxes)[selected_index];
      
      GetTensorData<float>(detection_classes)[box_offset] = class_indices[col];
      
      GetTensorData<float>(detection_scores)[box_offset] =
          box_scores[class_indices[col]];
      output_box_index++;
    }
  }
  GetTensorData<float>(num_detections)[0] = output_box_index;
  return kTfLiteOk;
}