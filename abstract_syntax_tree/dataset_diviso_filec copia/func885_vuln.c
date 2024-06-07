    CompressionHeader(ConstDataRangeCursor* cursor) {
        originalOpCode = cursor->readAndAdvance<LittleEndian<std::int32_t>>().getValue();
        uncompressedSize = cursor->readAndAdvance<LittleEndian<std::int32_t>>().getValue();
        compressorId = cursor->readAndAdvance<LittleEndian<uint8_t>>().getValue();
    }