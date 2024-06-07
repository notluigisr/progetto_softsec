    XPathIo::XPathIo(const std::string& orgPath) : FileIo(XPathIo::writeDataToFile(orgPath)) {
        isTemp_ = true;
        tempFilePath_ = path();
    }