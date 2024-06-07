inline uint8_t* WireFormatLite::WriteUInt32NoTagToArray(
    const RepeatedField<uint32_t>& value, uint8_t* target) {
  return WritePrimitiveNoTagToArray(value, WriteUInt32NoTagToArray, target);
}