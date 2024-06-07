httpSpecialDoSide(HTTPRequestPtr requestor)
{
    HTTPConnectionPtr client = requestor->connection;

    if (readFinished(client))
        return 1;   
 
    if(client->reqbegin > 0 && client->reqlen > client->reqbegin) {
        memmove(client->reqbuf, client->reqbuf + client->reqbegin,
                client->reqlen - client->reqbegin);
    }
    client->reqlen -= client->reqbegin;
    client->reqbegin = 0;

    do_stream(IO_READ | IO_NOTNOW, client->fd,
              client->reqlen, client->reqbuf, MAXBODY(client),
              httpSpecialClientSideHandler, client);
    return 1;
}