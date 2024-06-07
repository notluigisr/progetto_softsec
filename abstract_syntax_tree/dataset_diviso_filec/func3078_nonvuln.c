ConnStateData::afterClientRead()
{
#if USE_OPENSSL
    if (parsingTlsHandshake) {
        parseTlsHandshake();
        return;
    }
#endif

    
    if (pipeline.empty())
        fd_note(clientConnection->fd, "STR");

    if (!clientParseRequests()) {
        if (!isOpen())
            return;
        
        
        
        if (pipeline.empty() && commIsHalfClosed(clientConnection->fd)) {
            debugs(33, 5, clientConnection << "STR");
            clientConnection->close();
            return;
        }
    }

    if (!isOpen())
        return;

    clientAfterReadingRequests();
}