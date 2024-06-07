    const std::array<unsigned char, 16> uuid() const {
        int len = 0;
        const char* data = nullptr;
        if (type() == BinData && binDataType() == BinDataType::newUUID)
            data = binData(len);
        uassert(ErrorCodes::InvalidUUID,
                "STR",
                len == 16);
        std::array<unsigned char, 16> result;
        memcpy(&result, data, len);
        return result;
    }