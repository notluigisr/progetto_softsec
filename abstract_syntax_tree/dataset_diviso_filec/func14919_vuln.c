writeBufferToSeparateStrips (TIFF* out, uint8* buf, 
			     uint32 length, uint32 width, uint16 spp,
			     struct dump_opts *dump)
  {
  uint8   *src;
  uint16   bps;
  uint32   row, nrows, rowsize, rowsperstrip;
  uint32   bytes_per_sample;
  tsample_t s;
  tstrip_t strip = 0;
  tsize_t  stripsize = TIFFStripSize(out);
  tsize_t  rowstripsize,  scanlinesize = TIFFScanlineSize(out);
  tsize_t  total_bytes = 0;
  tdata_t  obuf;

  (void) TIFFGetFieldDefaulted(out, TIFFTAG_ROWSPERSTRIP, &rowsperstrip);
  (void) TIFFGetField(out, TIFFTAG_BITSPERSAMPLE, &bps);
  bytes_per_sample = (bps + 7) / 8;
  rowsize = ((bps * spp * width) + 7) / 8; 
  rowstripsize = rowsperstrip * bytes_per_sample * (width + 1); 

  obuf = _TIFFmalloc (rowstripsize);
  if (obuf == NULL)
    return 1;
  
  for (s = 0; s < spp; s++)
    {
    for (row = 0; row < length; row += rowsperstrip)
      {
      nrows = (row + rowsperstrip > length) ? length - row : rowsperstrip;

      stripsize = TIFFVStripSize(out, nrows);
      src = buf + (row * rowsize);
      total_bytes += stripsize;
      memset (obuf, '\0', rowstripsize);
      if (extractContigSamplesToBuffer(obuf, src, nrows, width, s, spp, bps, dump))
        {
        _TIFFfree(obuf);
        return 1;
	}
      if ((dump->outfile != NULL) && (dump->level == 1))
        {
        dump_info(dump->outfile, dump->format,"", 
                  "STR", 
                  s + 1, strip + 1, stripsize, row + 1, scanlinesize, src - buf);
        dump_buffer(dump->outfile, dump->format, nrows, scanlinesize, row, obuf);
	}

      if (TIFFWriteEncodedStrip(out, strip++, obuf, stripsize) < 0)
        {
	TIFFError(TIFFFileName(out), "STR", strip - 1);
	_TIFFfree(obuf);
	return 1;
	}
      }
    }      

  _TIFFfree(obuf);
  return 0;
}