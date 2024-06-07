    void serialize(DataRangeCursor* cursor) {
        cursor->writeAndAdvance<LittleEndian<int32_t>>(originalOpCode);
        cursor->writeAndAdvance<LittleEndian<int32_t>>(uncompressedSize);
        cursor->writeAndAdvance<LittleEndian<uint8_t>>(compressorId);
    }