bool WriteEbmlHeader(IMkvWriter* writer, uint64_t doc_type_version,
                     const char* const doc_type) {
  
  uint64_t size =
      EbmlElementSize(libwebm::kMkvEBMLVersion, static_cast<uint64>(1));
  size += EbmlElementSize(libwebm::kMkvEBMLReadVersion, static_cast<uint64>(1));
  size += EbmlElementSize(libwebm::kMkvEBMLMaxIDLength, static_cast<uint64>(4));
  size +=
      EbmlElementSize(libwebm::kMkvEBMLMaxSizeLength, static_cast<uint64>(8));
  size += EbmlElementSize(libwebm::kMkvDocType, doc_type);
  size += EbmlElementSize(libwebm::kMkvDocTypeVersion,
                          static_cast<uint64>(doc_type_version));
  size +=
      EbmlElementSize(libwebm::kMkvDocTypeReadVersion, static_cast<uint64>(2));

  if (!WriteEbmlMasterElement(writer, libwebm::kMkvEBML, size))
    return false;
  if (!WriteEbmlElement(writer, libwebm::kMkvEBMLVersion,
                        static_cast<uint64>(1))) {
    return false;
  }
  if (!WriteEbmlElement(writer, libwebm::kMkvEBMLReadVersion,
                        static_cast<uint64>(1))) {
    return false;
  }
  if (!WriteEbmlElement(writer, libwebm::kMkvEBMLMaxIDLength,
                        static_cast<uint64>(4))) {
    return false;
  }
  if (!WriteEbmlElement(writer, libwebm::kMkvEBMLMaxSizeLength,
                        static_cast<uint64>(8))) {
    return false;
  }
  if (!WriteEbmlElement(writer, libwebm::kMkvDocType, doc_type))
    return false;
  if (!WriteEbmlElement(writer, libwebm::kMkvDocTypeVersion,
                        static_cast<uint64>(doc_type_version))) {
    return false;
  }
  if (!WriteEbmlElement(writer, libwebm::kMkvDocTypeReadVersion,
                        static_cast<uint64>(2))) {
    return false;
  }

  return true;
}