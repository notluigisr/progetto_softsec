DetectSmoothImage24 (rfbClientPtr cl,
                     rfbPixelFormat *fmt,
                     int w,
                     int h)
{
    int off;
    int x, y, d, dx, c;
    int diffStat[256];
    int pixelCount = 0;
    int pix, left[3];
    unsigned long avgError;

    
    off = (fmt->bigEndian != 0);

    memset(diffStat, 0, 256*sizeof(int));

    y = 0, x = 0;
    while (y < h && x < w) {
        for (d = 0; d < h - y && d < w - x - DETECT_SUBROW_WIDTH; d++) {
            for (c = 0; c < 3; c++) {
                left[c] = (int)tightBeforeBuf[((y+d)*w+x+d)*4+off+c] & 0xFF;
            }
            for (dx = 1; dx <= DETECT_SUBROW_WIDTH; dx++) {
                for (c = 0; c < 3; c++) {
                    pix = (int)tightBeforeBuf[((y+d)*w+x+d+dx)*4+off+c] & 0xFF;
                    diffStat[abs(pix - left[c])]++;
                    left[c] = pix;
                }
                pixelCount++;
            }
        }
        if (w > h) {
            x += h;
            y = 0;
        } else {
            x = 0;
            y += w;
        }
    }

    if (diffStat[0] * 33 / pixelCount >= 95)
        return 0;

    avgError = 0;
    for (c = 1; c < 8; c++) {
        avgError += (unsigned long)diffStat[c] * (unsigned long)(c * c);
        if (diffStat[c] == 0 || diffStat[c] > diffStat[c-1] * 2)
            return 0;
    }
    for (; c < 256; c++) {
        avgError += (unsigned long)diffStat[c] * (unsigned long)(c * c);
    }
    avgError /= (pixelCount * 3 - diffStat[0]);

    return avgError;
}