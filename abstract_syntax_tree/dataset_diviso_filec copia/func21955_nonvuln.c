delayedHttpClientContinue(HTTPConnectionPtr connection)
{
    TimeEventHandlerPtr event;
    event = scheduleTimeEvent(-1, httpClientContinueDelayed,
                              sizeof(connection), &connection);
    if(!event)
        return -1;
    return 1;
}