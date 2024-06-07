void CoreNetwork::networkInitialized()
{
    setConnectionState(Network::Initialized);
    setConnected(true);
    _quitRequested = false;

    if (useAutoReconnect()) {
        
        _autoReconnectCount = unlimitedReconnectRetries() ? -1 : autoReconnectRetries();
    }

    
    QString awayMsg = Core::awayMessage(userId(), networkId());
    if (!awayMsg.isEmpty())
        userInputHandler()->handleAway(BufferInfo(), Core::awayMessage(userId(), networkId()));

    sendPerform();

    _sendPings = true;

    if (networkConfig()->autoWhoEnabled()) {
        _autoWhoCycleTimer.start();
        _autoWhoTimer.start();
        startAutoWhoCycle(); 
    }

    Core::bufferInfo(userId(), networkId(), BufferInfo::StatusBuffer); 
    Core::setNetworkConnected(userId(), networkId(), true);
}