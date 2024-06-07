TfLiteRegistration* Register_LOGICAL_NOT() {
  static TfLiteRegistration r = {
      nullptr, nullptr,
      elementwise::GenericPrepare<elementwise::IsLogicalSupportedType,
                                  elementwise::kNotName>,
      elementwise::LogicalNotEval};
  return &r;
}