void edge_filtering_luma_CTB(de265_image* img, bool vertical, int xCtb,int yCtb)
{
  int ctbSize = img->get_sps().CtbSizeY;
  int deblkSize = ctbSize/4;

  edge_filtering_luma(img,vertical,
                      yCtb*deblkSize, (yCtb+1)*deblkSize,
                      xCtb*deblkSize, (xCtb+1)*deblkSize);
}