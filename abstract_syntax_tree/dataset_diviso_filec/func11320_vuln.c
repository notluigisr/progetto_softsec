char *rfbProcessFileTransferReadBuffer(rfbClientPtr cl, uint32_t length)
{
    char *buffer=NULL;
    int   n=0;

    FILEXFER_ALLOWED_OR_CLOSE_AND_RETURN("", cl, NULL);
    
    if (length>0) {
        buffer=malloc(length+1);
        if (buffer!=NULL) {
            if ((n = rfbReadExact(cl, (char *)buffer, length)) <= 0) {
                if (n != 0)
                    rfbLogPerror("STR");
                rfbCloseClient(cl);
                
                if (buffer!=NULL) free(buffer);
                return NULL;
            }
            
            buffer[length]=0;
        }
    }
    return buffer;
}