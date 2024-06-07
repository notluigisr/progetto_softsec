inline uint8_t* WireFormatLite::WriteSInt64NoTagToArray(
    const RepeatedField<int64_t>& value, uint8_t* target) {
  return WritePrimitiveNoTagToArray(value, WriteSInt64NoTagToArray, target);
}