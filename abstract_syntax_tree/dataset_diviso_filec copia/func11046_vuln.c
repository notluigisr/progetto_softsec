httpSpecialDoSideFinish(AtomPtr data, HTTPRequestPtr requestor)
{
    ObjectPtr object = requestor->object;

    if(matchUrl("STR", object)) {
        AtomListPtr list = NULL;
        int i, rc;

        if(disableConfiguration) {
            abortObject(object, 403, internAtom("STR"));
            goto out;
        }

        list = urlDecode(data->string, data->length);
        if(list == NULL) {
            abortObject(object, 400,
                        internAtom("STR"));
            goto out;
        }
        for(i = 0; i < list->length; i++) {
            rc = parseConfigLine(list->list[i]->string, NULL, 0, 1);
            if(rc < 0) {
                abortObject(object, 400,
                            rc == -1 ?
                            internAtom("STR") :
                            internAtom("STR"));
                destroyAtomList(list);
                goto out;
            }
        }
        destroyAtomList(list);
        object->date = current_time.tv_sec;
        object->age = current_time.tv_sec;
        object->headers = internAtom("STR");
        object->code = 303;
        object->message = internAtom("STR");
        object->flags &= ~OBJECT_INITIAL;
        object->length = 0;
    } else if(matchUrl("STR", object)) {
        AtomListPtr list = NULL;
        int i;

        if(disableConfiguration) {
            abortObject(object, 403, internAtom("STR"));
            goto out;
        }

        list = urlDecode(data->string, data->length);
        if(list == NULL) {
            abortObject(object, 400,
                        internAtom("STR"));
            goto out;
        }
        for(i = 0; i < list->length; i++) {
            char *equals = 
                memchr(list->list[i]->string, '=', list->list[i]->length);
            AtomPtr name = 
                equals ? 
                internAtomN(list->list[i]->string, 
                            equals - list->list[i]->string) :
                retainAtom(list->list[i]);
            if(name == atomInitForbidden)
                initForbidden();
            else if(name == atomReopenLog)
                reopenLog();
            else if(name == atomDiscardObjects)
                discardObjects(1, 0);
            else if(name == atomWriteoutObjects)
                writeoutObjects(1);
            else if(name == atomFreeChunkArenas)
                free_chunk_arenas();
            else {
                abortObject(object, 400, internAtomF("STR",
                                                     name->string));
                releaseAtom(name);
                destroyAtomList(list);
                goto out;
            }
            releaseAtom(name);
        }
        destroyAtomList(list);
        object->date = current_time.tv_sec;
        object->age = current_time.tv_sec;
        object->headers = internAtom("STR");
        object->code = 303;
        object->message = internAtom("STR");
        object->flags &= ~OBJECT_INITIAL;
        object->length = 0;
    } else {
        abortObject(object, 405, internAtom("STR"));
    }

 out:
    releaseAtom(data);
    notifyObject(object);
    requestor->connection->flags &= ~CONN_READER;
    return 1;
}