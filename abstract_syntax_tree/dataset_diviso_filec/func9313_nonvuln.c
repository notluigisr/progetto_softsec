void CoreNetwork::setUseAutoReconnect(bool use)
{
    Network::setUseAutoReconnect(use);
    if (!use)
        _autoReconnectTimer.stop();
}