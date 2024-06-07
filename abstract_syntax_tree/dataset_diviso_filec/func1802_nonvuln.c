ProcPanoramiXShmPutImage(register ClientPtr client)
{
    int			 j, result = 0, orig_x, orig_y;
    PanoramiXRes	*draw, *gc;
    Bool		 sendEvent, isRoot;

    REQUEST(xShmPutImageReq);
    REQUEST_SIZE_MATCH(xShmPutImageReq);

    if(!(draw = (PanoramiXRes *)SecurityLookupIDByClass(
                client, stuff->drawable, XRC_DRAWABLE, DixWriteAccess)))
        return BadDrawable;

    if(!(gc = (PanoramiXRes *)SecurityLookupIDByType(
                client, stuff->gc, XRT_GC, DixReadAccess)))
        return BadGC;

    isRoot = (draw->type == XRT_WINDOW) && draw->u.win.root;

    orig_x = stuff->dstX;
    orig_y = stuff->dstY;
    sendEvent = stuff->sendEvent;
    stuff->sendEvent = 0;
    FOR_NSCREENS(j) {
	if(!j) stuff->sendEvent = sendEvent;
	stuff->drawable = draw->info[j].id;
	stuff->gc = gc->info[j].id;
	if (isRoot) {
	    stuff->dstX = orig_x - panoramiXdataPtr[j].x;
	    stuff->dstY = orig_y - panoramiXdataPtr[j].y;
	}
	result = ProcShmPutImage(client);
	if(result != client->noClientException) break;
    }
    return(result);
}