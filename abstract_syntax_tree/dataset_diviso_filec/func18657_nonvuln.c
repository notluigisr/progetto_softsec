void CLASS kodak_65000_load_raw()
{
  short buf[272]; 
  int row, col, len, pred[2], ret, i;

  for (row=0; row < height; row++)
  {
#ifdef LIBRAW_LIBRARY_BUILD
    checkCancel();
#endif
    for (col=0; col < width; col+=256) {
      pred[0] = pred[1] = 0;
      len = MIN (256, width-col);
      ret = kodak_65000_decode (buf, len);
      for (i=0; i < len; i++)
      {
	int idx = ret ? buf[i] : (pred[i & 1] += buf[i]);
	if(idx >=0 && idx <= 0xffff)
	 {
	   if ((RAW(row,col+i) = curve[idx]) >> 12) derror();
         }
	 else
	   derror();
      }
    }
  }
}