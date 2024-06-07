XStoreNamedColor(
register Display *dpy,
Colormap cmap,
_Xconst char *name, 
unsigned long pixel, 
int flags)  
{
    unsigned int nbytes;
    register xStoreNamedColorReq *req;
    XcmsCCC ccc;
    XcmsColor cmsColor_exact;
    XColor scr_def;

#ifdef XCMS
    
    if ((ccc = XcmsCCCOfColormap(dpy, cmap)) != (XcmsCCC)NULL) {
	if (_XcmsResolveColorString(ccc, &name, &cmsColor_exact,
		XcmsRGBFormat) >= XcmsSuccess) {
	    _XcmsRGB_to_XColor(&cmsColor_exact, &scr_def, 1);
	    scr_def.pixel = pixel;
	    scr_def.flags = flags;
	    return XStoreColor(dpy, cmap, &scr_def);
	}
	
    }
#endif

    

    LockDisplay(dpy);
    GetReq(StoreNamedColor, req);

    req->cmap = cmap;
    req->flags = flags;
    req->pixel = pixel;
    req->nbytes = (CARD16) (nbytes = (unsigned) strlen(name));
    req->length += (nbytes + 3) >> 2; 
    Data(dpy, name, (long)nbytes);
    UnlockDisplay(dpy);
    SyncHandle();
    return 0;
}