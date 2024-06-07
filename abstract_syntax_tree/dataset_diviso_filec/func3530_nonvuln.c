rfbProcessClientProtocolVersion(rfbClientPtr cl)
{
    rfbProtocolVersionMsg pv;
    int n, major_, minor_;

    if ((n = ReadExact(cl, pv, sz_rfbProtocolVersionMsg)) <= 0) {
        if (n == 0)
            rfbLog("STR");
        else
            rfbLogPerror("STR");
        rfbCloseClient(cl);
        return;
    }

    pv[sz_rfbProtocolVersionMsg] = 0;
    if (sscanf(pv,rfbProtocolVersionFormat,&major_,&minor_) != 2) {
        char name[1024]; 
	if(sscanf(pv,"STR",&major_,&minor_,name) != 3) {
	    rfbErr("STR");
	    rfbCloseClient(cl);
	    return;
	}
	free(cl->host);
	cl->host=strdup(name);
    }
    rfbLog("STR", major_, minor_);

    if (major_ != rfbProtocolMajorVersion) {
        rfbErr("STR",
                rfbProtocolMajorVersion, rfbProtocolMinorVersion7,
                major_,minor_);
        rfbCloseClient(cl);
        return;
    }

    if (minor_ != rfbProtocolMinorVersion3 &&
	minor_ != rfbProtocolMinorVersion7 &&
	minor_ != rfbProtocolMinorVersion8) {
        
        rfbLog("STR");
    }

    if (minor_ >= rfbProtocolMinorVersion8)
      cl->minorVersion = rfbProtocolMinorVersion8;
    else if (minor_ == rfbProtocolMinorVersion7)
      cl->minorVersion = rfbProtocolMinorVersion7;
    else
      cl->minorVersion = rfbProtocolMinorVersion3;

    rfbAuthNewClient(cl);
}