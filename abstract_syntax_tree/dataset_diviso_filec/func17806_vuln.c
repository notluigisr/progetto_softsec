XQueryExtension(
    register Display *dpy,
    _Xconst char *name,
    int *major_opcode,  
    int *first_event,   
    int *first_error)	
{
    xQueryExtensionReply rep;
    register xQueryExtensionReq *req;

    LockDisplay(dpy);
    GetReq(QueryExtension, req);
    req->nbytes = name ? (CARD16) strlen(name) : 0;
    req->length += (req->nbytes+(unsigned)3)>>2;
    _XSend(dpy, name, (long)req->nbytes);
    (void) _XReply (dpy, (xReply *)&rep, 0, xTrue);
    *major_opcode = rep.major_opcode;
    *first_event = rep.first_event;
    *first_error = rep.first_error;
    UnlockDisplay(dpy);
    SyncHandle();
    return (rep.present);
}