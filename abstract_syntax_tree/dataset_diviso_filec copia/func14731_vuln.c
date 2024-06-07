httpSpecialClientSideHandler(int status,
                             FdEventHandlerPtr event,
                             StreamRequestPtr srequest)
{
    HTTPConnectionPtr connection = srequest->data;
    HTTPRequestPtr request = connection->request;
    int push;

    if((request->object->flags & OBJECT_ABORTED) || 
       !(request->object->flags & OBJECT_INPROGRESS)) {
        httpClientDiscardBody(connection);
        httpClientError(request, 503, internAtom("STR"));
        return 1;
    }
        
    if(status < 0) {
        do_log_error(L_ERROR, -status, "STR");
        if(status == -EDOGRACEFUL)
            httpClientFinish(connection, 1);
        else
            httpClientFinish(connection, 2);
        return 1;
    }

    push = MIN(srequest->offset - connection->reqlen,
               connection->bodylen - connection->reqoffset);
    if(push > 0) {
        connection->reqlen += push;
        httpSpecialDoSide(request);
    }

    do_log(L_ERROR, "STR");
    connection->flags &= ~CONN_READER;
    httpClientRawError(connection, 502,
                       internAtom("STR"), 1);
    return 1;
}