rfbSendServerCutText(rfbScreenInfoPtr rfbScreen,char *str, int len)
{
    rfbClientPtr cl;
    rfbServerCutTextMsg sct;
    rfbClientIteratorPtr iterator;

    iterator = rfbGetClientIterator(rfbScreen);
    while ((cl = rfbClientIteratorNext(iterator)) != NULL) {
        sct.type = rfbServerCutText;
        sct.length = Swap32IfLE(len);
        if (WriteExact(cl, (char *)&sct,
                       sz_rfbServerCutTextMsg) < 0) {
            rfbLogPerror("STR");
            rfbCloseClient(cl);
            continue;
        }
        if (WriteExact(cl, str, len) < 0) {
            rfbLogPerror("STR");
            rfbCloseClient(cl);
        }
    }
    rfbReleaseClientIterator(iterator);
}