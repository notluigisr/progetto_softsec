StatusWith<std::size_t> SnappyMessageCompressor::decompressData(ConstDataRange input,
                                                                DataRange output) {
    try {
        uint32_t expectedLength = 0;
        ConstDataRangeSource lengthCheckSource(input);
        if (!snappy::GetUncompressedLength(&lengthCheckSource, &expectedLength) ||
            expectedLength > output.length()) {
            return {ErrorCodes::BadValue, "STR"};
        }

        ConstDataRangeSource source(input);
        DataRangeSink sink(output);

        bool ret = snappy::Uncompress(&source, &sink);
        if (!ret) {
            return Status{ErrorCodes::BadValue, "STR"};
        }
    } catch (const SnappySourceSinkException& e) {
        return e.toStatus();
    }

    counterHitDecompress(input.length(), output.length());
    return output.length();
}