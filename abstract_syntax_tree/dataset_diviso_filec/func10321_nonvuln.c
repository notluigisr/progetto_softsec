inline void WireFormatLite::WriteSFixed32NoTag(int32_t value,
                                               io::CodedOutputStream* output) {
  output->WriteLittleEndian32(static_cast<uint32_t>(value));
}