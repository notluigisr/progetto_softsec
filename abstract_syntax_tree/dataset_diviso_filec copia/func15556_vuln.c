rfbBool rfbSendFileTransferMessage(rfbClientPtr cl, uint8_t contentType, uint8_t contentParam, uint32_t size, uint32_t length, char *buffer)
{
    rfbFileTransferMsg ft;
    ft.type = rfbFileTransfer;
    ft.contentType = contentType;
    ft.contentParam = contentParam;
    ft.pad          = 0; 
    ft.size         = Swap32IfLE(size);
    ft.length       = Swap32IfLE(length);
    
    FILEXFER_ALLOWED_OR_CLOSE_AND_RETURN("", cl, FALSE);
    
    if (rfbWriteExact(cl, (char *)&ft, sz_rfbFileTransferMsg) < 0) {
        rfbLogPerror("STR");
        rfbCloseClient(cl);
        return FALSE;
    }

    if (length>0)
    {
        if (rfbWriteExact(cl, buffer, length) < 0) {
            rfbLogPerror("STR");
            rfbCloseClient(cl);
            return FALSE;
        }
    }

    rfbStatRecordMessageSent(cl, rfbFileTransfer, sz_rfbFileTransferMsg+length, sz_rfbFileTransferMsg+length);

    return TRUE;
}