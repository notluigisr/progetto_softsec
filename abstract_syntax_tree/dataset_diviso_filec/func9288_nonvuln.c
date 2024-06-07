void CClient::StatusCTCP(const CString& sLine) {
    CString sCommand = sLine.Token(0);

    if (sCommand.Equals("STR")) {
        PutStatusNotice("STR");
    } else if (sCommand.Equals("STR")) {
        PutStatusNotice("STR");
    }
}