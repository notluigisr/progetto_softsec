void CLASS write_ppm_tiff()
{
  struct tiff_hdr th;
  uchar *ppm;
  ushort *ppm2;
  int c, row, col, soff, rstep, cstep;
  int perc, val, total, t_white=0x2000;

#ifdef LIBRAW_LIBRARY_BUILD
  perc = width * height * auto_bright_thr;		
#else
  perc = width * height * 0.01;		
#endif
  if (fuji_width) perc /= 2;
  if (!((highlight & ~2) || no_auto_bright))
    for (t_white=c=0; c < colors; c++) {
      for (val=0x2000, total=0; --val > 32; )
	if ((total += histogram[c][val]) > perc) break;
      if (t_white < val) t_white = val;
    }
  gamma_curve (gamm[0], gamm[1], 2, (t_white << 3)/bright);
  iheight = height;
  iwidth  = width;
  if (flip & 4) SWAP(height,width);
  ppm = (uchar *) calloc (width, colors*output_bps/8);
  ppm2 = (ushort *) ppm;
  merror (ppm, "STR");
  if (output_tiff) {
    tiff_head (&th, 1);
    fwrite (&th, sizeof th, 1, ofp);
    if (oprof)
      fwrite (oprof, ntohl(oprof[0]), 1, ofp);
  } else if (colors > 3)
    fprintf (ofp,
      "STR",
	width, height, colors, (1 << output_bps)-1, cdesc);
  else
    fprintf (ofp, "STR",
	colors/2+5, width, height, (1 << output_bps)-1);
  soff  = flip_index (0, 0);
  cstep = flip_index (0, 1) - soff;
  rstep = flip_index (1, 0) - flip_index (0, width);
  for (row=0; row < height; row++, soff += rstep) {
    for (col=0; col < width; col++, soff += cstep)
      if (output_bps == 8)
	   FORCC ppm [col*colors+c] = curve[image[soff][c]] >> 8;
      else FORCC ppm2[col*colors+c] = curve[image[soff][c]];
    if (output_bps == 16 && !output_tiff && htons(0x55aa) != 0x55aa)
      swab ((char*)ppm2, (char*)ppm2, width*colors*2);
    fwrite (ppm, colors*output_bps/8, width, ofp);
  }
  free (ppm);
}