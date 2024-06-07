inline uint8_t* WireFormatLite::WriteSFixed32NoTagToArray(int32_t value,
                                                          uint8_t* target) {
  return io::CodedOutputStream::WriteLittleEndian32ToArray(
      static_cast<uint32_t>(value), target);
}