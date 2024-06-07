bool ValidateBoxes(const TfLiteTensor* decoded_boxes, const int num_boxes) {
  for (int i = 0; i < num_boxes; ++i) {
    
    auto& box = ReInterpretTensor<const BoxCornerEncoding*>(decoded_boxes)[i];
    if (box.ymin >= box.ymax || box.xmin >= box.xmax) {
      return false;
    }
  }
  return true;
}