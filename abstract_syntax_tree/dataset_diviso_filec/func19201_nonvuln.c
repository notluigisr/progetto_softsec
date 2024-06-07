void CLASS panasonic_load_raw()
{
  int row, col, i, j, sh=0, pred[2], nonz[2];

  pana_bits(0);
  for (row=0; row < height; row++)
    for (col=0; col < raw_width; col++) {
      if ((i = col % 14) == 0)
	pred[0] = pred[1] = nonz[0] = nonz[1] = 0;
      if (i % 3 == 2) sh = 4 >> (3 - pana_bits(2));
      if (nonz[i & 1]) {
	if ((j = pana_bits(8))) {
	  if ((pred[i & 1] -= 0x80 << sh) < 0 || sh == 4)
	       pred[i & 1] &= ~(-1 << sh);
	  pred[i & 1] += j << sh;
	}
      } else if ((nonz[i & 1] = pana_bits(8)) || i > 11)
	pred[i & 1] = nonz[i & 1] << 4 | pana_bits(4);
#ifndef LIBRAW_LIBRARY_BUILD
      if (col < width)
              if ((BAYER(row,col) = pred[col & 1]) > 4098) derror();
#else
      RBAYER(row,col) = pred[col & 1];
      if (col < width)
          if (RBAYER(row,col) > 4098) derror();
#endif
    }
}