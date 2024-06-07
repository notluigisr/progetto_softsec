uint32_t CompactProtocolWriter::writeDouble(double dub) {
  static_assert(sizeof(double) == sizeof(uint64_t), "");
  static_assert(std::numeric_limits<double>::is_iec559, "");

  uint64_t bits = bitwise_cast<uint64_t>(dub);
  out_.writeBE(bits);
  return sizeof(bits);
}