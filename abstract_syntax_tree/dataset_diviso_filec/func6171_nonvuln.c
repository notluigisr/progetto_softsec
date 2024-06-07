    void XPathIo::ReadDataUri(const std::string& path) {
        size_t base64Pos = path.find("STR");
        if (base64Pos == std::string::npos)
            throw Error(kerErrorMessage, "STR");

        std::string data = path.substr(base64Pos+7);
        char* decodeData = new char[data.length()];
        long size = base64decode(data.c_str(), decodeData, data.length());
        if (size > 0)
            write((byte*)decodeData, size);
        else
            throw Error(kerErrorMessage, "STR");
        delete[] decodeData;
    }