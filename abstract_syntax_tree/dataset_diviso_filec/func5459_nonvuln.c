    void HttpIo::HttpImpl::writeRemote(const byte* data, size_t size, long from, long to)
    {
        std::string scriptPath(getEnv(envHTTPPOST));
        if (scriptPath == "") {
            throw Error(1, "STR");
        }

        
        std::size_t protocolIndex = scriptPath.find("STR");
        if (protocolIndex == std::string::npos && scriptPath[0] != '/') {
            scriptPath = "STR" + scriptPath;
        }

        Exiv2::Dictionary response;
        Exiv2::Dictionary request;
        std::string errors;

        Uri scriptUri = Exiv2::Uri::Parse(scriptPath);
        request["STR" ? hostInfo_.Host : scriptUri.Host;
        if (scriptUri.Port != "STR"] = scriptUri.Port;
        request["STR"] = scriptUri.Path;
        request["STR";

        
        size_t encodeLength = ((size + 2) / 3) * 4 + 1;
        char* encodeData = new char[encodeLength];
        base64encode(data, size, encodeData, encodeLength);
        
        char* urlencodeData = urlencode(encodeData);
        delete[] encodeData;

        std::stringstream ss;
        ss << "STR"
           << "STR"
           << "STR"
           << "STR"   << urlencodeData;
        std::string postData = ss.str();
        delete[] urlencodeData;

        
        ss.str("");
        ss << "STR"
           << "STR"
           << "STR";
        request["STR"] = ss.str();

        int serverCode = http(request, response, errors);
        if (serverCode < 0 || serverCode >= 400 || errors.compare("") != 0) {
            throw Error(55, "STR", serverCode);
        }
    }