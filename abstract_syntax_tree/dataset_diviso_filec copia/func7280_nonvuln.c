httpServeChunkDelayed(TimeEventHandlerPtr event)
{
    HTTPConnectionPtr connection = *(HTTPConnectionPtr*)event->data;
    unlockChunk(connection->request->object,
                connection->offset / CHUNK_SIZE);
    httpServeChunk(connection);
    return 1;
}