hufUncompress (const char compressed[],
	       int nCompressed,
	       unsigned short raw[],
	       int nRaw)
{
    if (nCompressed == 0)
    {
	if (nRaw != 0)
	    notEnoughData();

	return;
    }

    int im = readUInt (compressed);
    int iM = readUInt (compressed + 4);
    
    int nBits = readUInt (compressed + 12);

    if (im < 0 || im >= HUF_ENCSIZE || iM < 0 || iM >= HUF_ENCSIZE)
	invalidTableSize();

    const char *ptr = compressed + 20;

    
    
    
    
    

    if (FastHufDecoder::enabled() && nBits > 128)
    {
        FastHufDecoder fhd (ptr, nCompressed - (ptr - compressed), im, iM, iM);
        fhd.decode ((unsigned char*)ptr, nBits, raw, nRaw);
    }
    else
    {
        AutoArray <Int64, HUF_ENCSIZE> freq;
        AutoArray <HufDec, HUF_DECSIZE> hdec;

        hufClearDecTable (hdec);

        hufUnpackEncTable (&ptr,
                           nCompressed - (ptr - compressed),
                           im,
                           iM,
                           freq);

        try
        {
            if (nBits > 8 * (nCompressed - (ptr - compressed)))
                invalidNBits();

            hufBuildDecTable (freq, im, iM, hdec);
            hufDecode (freq, hdec, ptr, nBits, iM, nRaw, raw);
        }
        catch (...)
        {
            hufFreeDecTable (hdec);
            throw;
        }

        hufFreeDecTable (hdec);
    }
}