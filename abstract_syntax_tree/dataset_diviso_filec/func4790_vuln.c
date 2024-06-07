XAllocNamedColor(
register Display *dpy,
Colormap cmap,
_Xconst char *colorname, 
XColor *hard_def, 
XColor *exact_def) 
{

    long nbytes;
    xAllocNamedColorReply rep;
    xAllocNamedColorReq *req;

    XcmsCCC ccc;
    XcmsColor cmsColor_exact;
    Status ret;

#ifdef XCMS
    
    if ((ccc = XcmsCCCOfColormap(dpy, cmap)) != (XcmsCCC)NULL) {
	const char *tmpName = colorname;

	switch (_XcmsResolveColorString(ccc, &tmpName, &cmsColor_exact,
					XcmsRGBFormat)) {
	case XcmsSuccess:
	case XcmsSuccessWithCompression:
	    _XcmsRGB_to_XColor(&cmsColor_exact, exact_def, 1);
	    memcpy((char *)hard_def, (char *)exact_def, sizeof(XColor));
	    ret = XAllocColor(dpy, cmap, hard_def);
	    exact_def->pixel = hard_def->pixel;
	    return(ret);
	case XcmsFailure:
	case _XCMS_NEWNAME:
	    
	    break;
	}
    }
#endif

    
    LockDisplay(dpy);
    GetReq(AllocNamedColor, req);

    req->cmap = cmap;
    nbytes = req->nbytes = (CARD16) strlen(colorname);
    req->length += (nbytes + 3) >> 2; 

    _XSend(dpy, colorname, nbytes);
       

    if (!_XReply (dpy, (xReply *) &rep, 0, xTrue)) {
	UnlockDisplay(dpy);
        SyncHandle();
        return (0);
    }

    exact_def->red = rep.exactRed;
    exact_def->green = rep.exactGreen;
    exact_def->blue = rep.exactBlue;

    hard_def->red = rep.screenRed;
    hard_def->green = rep.screenGreen;
    hard_def->blue = rep.screenBlue;

    exact_def->pixel = hard_def->pixel = rep.pixel;

    UnlockDisplay(dpy);
    SyncHandle();
    return (1);
}