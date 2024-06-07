XSetStandardProperties (
    	Display *dpy,
    	Window w,		
    	_Xconst char *name,	
    	_Xconst char *icon_string,
	Pixmap icon_pixmap,	
    	char **argv,		
    	int argc,		
    	XSizeHints *hints)	
{
	XWMHints phints;
	phints.flags = 0;

	if (name != NULL) XStoreName (dpy, w, name);

	if (icon_string != NULL) {
	    XChangeProperty (dpy, w, XA_WM_ICON_NAME, XA_STRING, 8,
                             PropModeReplace,
                             (_Xconst unsigned char *)icon_string,
                             (int)safestrlen(icon_string));
		}

	if (icon_pixmap != None) {
		phints.icon_pixmap = icon_pixmap;
		phints.flags |= IconPixmapHint;
		}
	if (argv != NULL) XSetCommand(dpy, w, argv, argc);

	if (hints != NULL) XSetNormalHints(dpy, w, hints);

	if (phints.flags != 0) XSetWMHints(dpy, w, &phints);

	return 1;
}