inline bool WireFormatLite::ReadPrimitive<double, WireFormatLite::TYPE_DOUBLE>(
    io::CodedInputStream* input, double* value) {
  uint64_t temp;
  if (!input->ReadLittleEndian64(&temp)) return false;
  *value = DecodeDouble(temp);
  return true;
}