TfLiteRegistration* Register_TILE() {
  static TfLiteRegistration r = {nullptr, nullptr, tile::Prepare, tile::Eval};
  return &r;
}