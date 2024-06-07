CoreNetwork::~CoreNetwork()
{
    if (connectionState() != Disconnected && connectionState() != Network::Reconnecting)
        disconnectFromIrc(false);  
    disconnect(&socket, 0, this, 0); 
    delete _userInputHandler;
}