static int scsi_disk_emulate_inquiry(SCSIRequest *req, uint8_t *outbuf)
{
    SCSIDiskState *s = DO_UPCAST(SCSIDiskState, qdev, req->dev);
    int buflen = 0;

    if (req->cmd.buf[1] & 0x1) {
        
        return scsi_disk_emulate_vpd_page(req, outbuf);
    }

    
    if (req->cmd.buf[2] != 0) {
        return -1;
    }

    
    buflen = req->cmd.xfer;
    if (buflen > SCSI_MAX_INQUIRY_LEN) {
        buflen = SCSI_MAX_INQUIRY_LEN;
    }

    outbuf[0] = s->qdev.type & 0x1f;
    outbuf[1] = (s->features & (1 << SCSI_DISK_F_REMOVABLE)) ? 0x80 : 0;

    strpadcpy((char *) &outbuf[16], 16, s->product, ' ');
    strpadcpy((char *) &outbuf[8], 8, s->vendor, ' ');

    memset(&outbuf[32], 0, 4);
    memcpy(&outbuf[32], s->version, MIN(4, strlen(s->version)));
    
    outbuf[2] = s->qdev.default_scsi_version;
    outbuf[3] = 2 | 0x10; 

    if (buflen > 36) {
        outbuf[4] = buflen - 5; 
    } else {
        
        outbuf[4] = 36 - 5;
    }

    
    outbuf[7] = 0x10 | (req->bus->info->tcq ? 0x02 : 0);
    return buflen;
}