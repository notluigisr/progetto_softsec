httpsSslBumpAccessCheckDone(allow_t answer, void *data)
{
    ConnStateData *connState = (ConnStateData *) data;

    
    if (!connState->isOpen())
        return;

    if (answer.allowed()) {
        debugs(33, 2, "STR" << connState->clientConnection);
        connState->sslBumpMode = static_cast<Ssl::BumpMode>(answer.kind);
    } else {
        debugs(33, 3, "STR" << connState->clientConnection);
        connState->sslBumpMode = Ssl::bumpSplice;
    }

    if (connState->sslBumpMode == Ssl::bumpTerminate) {
        connState->clientConnection->close();
        return;
    }

    if (!connState->fakeAConnectRequest("STR", connState->inBuf))
        connState->clientConnection->close();
}