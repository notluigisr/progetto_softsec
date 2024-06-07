DECLAREContigPutFunc(putRGBcontig8bittile)
{
    int samplesperpixel = img->samplesperpixel;

    (void) x; (void) y;
    fromskew *= samplesperpixel;
    for( ; h > 0; --h) {
	UNROLL8(w, NOP,
	    *cp++ = PACK(pp[0], pp[1], pp[2]);
	    pp += samplesperpixel);
	cp += toskew;
	pp += fromskew;
    }
}