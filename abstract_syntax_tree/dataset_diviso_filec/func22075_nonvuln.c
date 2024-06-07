ConnStateData::transparent() const
{
    return clientConnection != NULL && (clientConnection->flags & (COMM_TRANSPARENT|COMM_INTERCEPTION));
}