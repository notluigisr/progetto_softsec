inline uint8_t* WireFormatLite::WriteSFixed32NoTagToArray(
    const RepeatedField<int32_t>& value, uint8_t* target) {
  return WriteFixedNoTagToArray(value, WriteSFixed32NoTagToArray, target);
}