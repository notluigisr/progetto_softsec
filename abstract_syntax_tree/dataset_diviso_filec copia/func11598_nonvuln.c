TfLiteRegistration* Register_SKIP_GRAM() {
  static TfLiteRegistration r = {nullptr, nullptr, Prepare, Eval};
  return &r;
}