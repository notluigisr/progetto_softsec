TfLiteRegistration* Register_NON_MAX_SUPPRESSION_V5() {
  static TfLiteRegistration r = {nullptr, nullptr, non_max_suppression::Prepare,
                                 non_max_suppression::Eval};
  return &r;
}