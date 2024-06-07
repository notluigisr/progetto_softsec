ConnStateData::endingShutdown()
{
    

    
    
    if (Comm::IsConnOpen(clientConnection))
        clientConnection->close();
}