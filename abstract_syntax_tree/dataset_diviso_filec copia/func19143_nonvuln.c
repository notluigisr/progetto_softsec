TfLiteRegistration* Register_DEPTH_TO_SPACE_GENERIC_OPT() {
  static TfLiteRegistration r = {
      nullptr, nullptr, depth_to_space::Prepare,
      depth_to_space::Eval<depth_to_space::kGenericOptimized>};
  return &r;
}