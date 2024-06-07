DECLAREContigPutFunc(put16bitbwtile)
{
    int samplesperpixel = img->samplesperpixel;
    uint32** BWmap = img->BWmap;

    (void) y;
    while (h-- > 0) {
        uint16 *wp = (uint16 *) pp;

	for (x = w; x-- > 0;)
        {
            

	    *cp++ = BWmap[*wp >> 8][0];
            pp += 2 * samplesperpixel;
            wp += samplesperpixel;
        }
	cp += toskew;
	pp += fromskew;
    }
}