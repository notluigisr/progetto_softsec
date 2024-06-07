uint32_t CompactProtocolWriter::serializedSizeZCBinary(
    std::unique_ptr<IOBuf> const& v) const {
  return v ? serializedSizeZCBinary(*v) : 0;
}