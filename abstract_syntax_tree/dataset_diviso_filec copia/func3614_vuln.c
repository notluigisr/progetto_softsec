read_non_rle_pixel(tga_source_ptr sinfo)

{
  register FILE *infile = sinfo->pub.input_file;
  register int i;

  for (i = 0; i < sinfo->pixel_size; i++) {
    sinfo->tga_pixel[i] = (U_CHAR)getc(infile);
  }
}