void markPredictionBlockBoundary(de265_image* img, int x0,int y0,
                                 int log2CbSize,
                                 int filterLeftCbEdge, int filterTopCbEdge)
{
  logtrace(LogDeblock,"STR",x0,y0,
           log2CbSize, filterLeftCbEdge,filterTopCbEdge);

  enum PartMode partMode = img->get_PartMode(x0,y0);

  int cbSize = 1<<log2CbSize;
  int cbSize2 = 1<<(log2CbSize-1);
  int cbSize4 = 1<<(log2CbSize-2);

  switch (partMode) {
  case PART_NxN:
    for (int k=0;k<cbSize;k++) {
      img->set_deblk_flags(x0+cbSize2,y0+k, DEBLOCK_PB_EDGE_VERTI);
      img->set_deblk_flags(x0+k,y0+cbSize2, DEBLOCK_PB_EDGE_HORIZ);
    }
    break;

  case PART_Nx2N:
    for (int k=0;k<cbSize;k++) {
      img->set_deblk_flags(x0+cbSize2,y0+k, DEBLOCK_PB_EDGE_VERTI);
    }
    break;

  case PART_2NxN:
    for (int k=0;k<cbSize;k++) {
      img->set_deblk_flags(x0+k,y0+cbSize2, DEBLOCK_PB_EDGE_HORIZ);
    }
    break;

  case PART_nLx2N:
    for (int k=0;k<cbSize;k++) {
      img->set_deblk_flags(x0+cbSize4,y0+k, DEBLOCK_PB_EDGE_VERTI);
    }
    break;

  case PART_nRx2N:
    for (int k=0;k<cbSize;k++) {
      img->set_deblk_flags(x0+cbSize2+cbSize4,y0+k, DEBLOCK_PB_EDGE_VERTI);
    }
    break;

  case PART_2NxnU:
    for (int k=0;k<cbSize;k++) {
      img->set_deblk_flags(x0+k,y0+cbSize4, DEBLOCK_PB_EDGE_HORIZ);
    }
    break;

  case PART_2NxnD:
    for (int k=0;k<cbSize;k++) {
      img->set_deblk_flags(x0+k,y0+cbSize2+cbSize4, DEBLOCK_PB_EDGE_HORIZ);
    }
    break;

  case PART_2Nx2N:
    
    break;
  }
}