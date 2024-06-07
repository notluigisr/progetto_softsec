httpSpecialDoSide(HTTPRequestPtr requestor)
{
    HTTPConnectionPtr client = requestor->connection;

    if(client->reqlen - client->reqbegin >= client->bodylen) {
        AtomPtr data;
        data = internAtomN(client->reqbuf + client->reqbegin,
                           client->reqlen - client->reqbegin);
        client->reqbegin = 0;
        client->reqlen = 0;
        if(data == NULL) {
            do_log(L_ERROR, "STR");
            httpClientError(requestor, 500,
                            internAtom("STR"));
            return 1;
        }
        httpSpecialDoSideFinish(data, requestor);
        return 1;
    }

    if(client->reqlen - client->reqbegin >= CHUNK_SIZE) {
        httpClientError(requestor, 500, internAtom("STR"));
        return 1;
    }

    if(client->reqbegin > 0 && client->reqlen > client->reqbegin) {
        memmove(client->reqbuf, client->reqbuf + client->reqbegin,
                client->reqlen - client->reqbegin);
    }
    client->reqlen -= client->reqbegin;
    client->reqbegin = 0;

    do_stream(IO_READ | IO_NOTNOW, client->fd,
              client->reqlen, client->reqbuf, CHUNK_SIZE,
              httpSpecialClientSideHandler, client);
    return 1;
}