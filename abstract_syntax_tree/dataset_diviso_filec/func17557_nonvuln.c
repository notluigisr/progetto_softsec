void* ReluInit(TfLiteContext* context, const char* buffer, size_t length) {
  return new ReluOpData;
}