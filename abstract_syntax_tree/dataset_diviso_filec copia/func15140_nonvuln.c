void HardSwishFree(TfLiteContext* context, void* buffer) {
  delete static_cast<HardSwishData*>(buffer);
}