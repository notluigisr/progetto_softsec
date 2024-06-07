httpLocalRequest(ObjectPtr object, int method, int from, int to,
                 HTTPRequestPtr requestor, void *closure)
{
    if(object->requestor == NULL)
        object->requestor = requestor;

    if(!disableLocalInterface && urlIsSpecial(object->key, object->key_size))
        return httpSpecialRequest(object, method, from, to, 
                                  requestor, closure);

    if(method >= METHOD_POST) {
        httpClientError(requestor, 405, internAtom("STR"));
        requestor->connection->flags &= ~CONN_READER;
        return 1;
    }

    
    if(object->flags & OBJECT_INITIAL) {
        abortObject(object, 404, internAtom("STR"));
    }
    object->age = current_time.tv_sec;
    object->date = current_time.tv_sec;

    object->flags &= ~OBJECT_VALIDATING;
    notifyObject(object);
    return 1;
}