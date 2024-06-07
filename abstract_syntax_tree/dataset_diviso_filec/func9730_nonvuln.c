ConnStateData::notePinnedConnectionBecameIdle(PinnedIdleContext pic)
{
    Must(pic.connection);
    Must(pic.request);
    pinConnection(pic.connection, *pic.request);

    
    startPinnedConnectionMonitoring();

    if (pipeline.empty())
        kick(); 
}