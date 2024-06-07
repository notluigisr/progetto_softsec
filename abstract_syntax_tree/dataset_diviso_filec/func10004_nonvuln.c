    std::string XPathIo::writeDataToFile(const std::wstring& wOrgPath) {
        std::string orgPath;
        orgPath.assign(wOrgPath.begin(), wOrgPath.end());
        return XPathIo::writeDataToFile(orgPath);
    }