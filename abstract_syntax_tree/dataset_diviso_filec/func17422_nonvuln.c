PrepareRowForJpeg(rfbClientPtr cl,
                  uint8_t *dst,
                  int x,
                  int y,
                  int count)
{
    if (cl->screen->serverFormat.bitsPerPixel == 32) {
        if ( cl->screen->serverFormat.redMax == 0xFF &&
             cl->screen->serverFormat.greenMax == 0xFF &&
             cl->screen->serverFormat.blueMax == 0xFF ) {
            PrepareRowForJpeg24(cl, dst, x, y, count);
        } else {
            PrepareRowForJpeg32(cl, dst, x, y, count);
        }
    } else {
        
        PrepareRowForJpeg16(cl, dst, x, y, count);
    }
}