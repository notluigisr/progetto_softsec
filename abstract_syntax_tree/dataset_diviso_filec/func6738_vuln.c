clientOutput(void *data)
{
    rfbClientPtr cl = (rfbClientPtr)data;
    rfbBool haveUpdate;
    sraRegion* updateRegion;

    while (1) {
        haveUpdate = false;
        while (!haveUpdate) {
            if (cl->sock == -1) {
                
                return NULL;
            }
	    LOCK(cl->updateMutex);
	    haveUpdate = FB_UPDATE_PENDING(cl);
	    if(!haveUpdate) {
		updateRegion = sraRgnCreateRgn(cl->modifiedRegion);
		haveUpdate = sraRgnAnd(updateRegion,cl->requestedRegion);
		sraRgnDestroy(updateRegion);
	    }

            if (!haveUpdate) {
                WAIT(cl->updateCond, cl->updateMutex);
            }
	    UNLOCK(cl->updateMutex);
        }
        
        
        usleep(cl->screen->deferUpdateTime * 1000);

        
        LOCK(cl->updateMutex);
	updateRegion = sraRgnCreateRgn(cl->modifiedRegion);
        UNLOCK(cl->updateMutex);

        
	rfbIncrClientRef(cl);
        rfbSendFramebufferUpdate(cl, updateRegion);
	rfbDecrClientRef(cl);

	sraRgnDestroy(updateRegion);
    }

    
    return NULL;
}