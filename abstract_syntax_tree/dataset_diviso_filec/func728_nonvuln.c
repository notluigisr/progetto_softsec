void httpsSslBumpStep2AccessCheckDone(Acl::Answer answer, void *data)
{
    ConnStateData *connState = (ConnStateData *) data;

    
    if (!connState->isOpen())
        return;

    debugs(33, 5, "STR" << answer.kind);
    assert(connState->serverBump());
    Ssl::BumpMode bumpAction;
    if (answer.allowed()) {
        bumpAction = (Ssl::BumpMode)answer.kind;
    } else
        bumpAction = Ssl::bumpSplice;

    connState->serverBump()->act.step2 = bumpAction;
    connState->sslBumpMode = bumpAction;
    Http::StreamPointer context = connState->pipeline.front();
    if (ClientHttpRequest *http = (context ? context->http : nullptr))
        http->al->ssl.bumpMode = bumpAction;

    if (bumpAction == Ssl::bumpTerminate) {
        connState->clientConnection->close();
    } else if (bumpAction != Ssl::bumpSplice) {
        connState->startPeekAndSplice();
    } else if (!connState->splice())
        connState->clientConnection->close();
}