ConnStateData::receivedFirstByte()
{
    if (receivedFirstByte_)
        return;

    receivedFirstByte_ = true;
    
    typedef CommCbMemFunT<ConnStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall =  JobCallback(33, 5,
                                      TimeoutDialer, this, ConnStateData::requestTimeout);
    commSetConnTimeout(clientConnection, Config.Timeout.request, timeoutCall);
}