    const std::array<unsigned char, 16> md5() const {
        int len = 0;
        const char* data = nullptr;
        if (type() == BinData && binDataType() == BinDataType::MD5Type)
            data = binData(len);
        uassert(40437, "STR", len == 16);
        std::array<unsigned char, 16> result;
        memcpy(&result, data, len);
        return result;
    }