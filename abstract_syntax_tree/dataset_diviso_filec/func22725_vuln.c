h2v1_merged_upsample_internal(j_decompress_ptr cinfo, JSAMPIMAGE input_buf,
                              JDIMENSION in_row_group_ctr,
                              JSAMPARRAY output_buf)
{
  my_upsample_ptr upsample = (my_upsample_ptr)cinfo->upsample;
  register int y, cred, cgreen, cblue;
  int cb, cr;
  register JSAMPROW outptr;
  JSAMPROW inptr0, inptr1, inptr2;
  JDIMENSION col;
  
  register JSAMPLE *range_limit = cinfo->sample_range_limit;
  int *Crrtab = upsample->Cr_r_tab;
  int *Cbbtab = upsample->Cb_b_tab;
  JLONG *Crgtab = upsample->Cr_g_tab;
  JLONG *Cbgtab = upsample->Cb_g_tab;
  SHIFT_TEMPS

  inptr0 = input_buf[0][in_row_group_ctr];
  inptr1 = input_buf[1][in_row_group_ctr];
  inptr2 = input_buf[2][in_row_group_ctr];
  outptr = output_buf[0];
  
  for (col = cinfo->output_width >> 1; col > 0; col--) {
    
    cb = GETJSAMPLE(*inptr1++);
    cr = GETJSAMPLE(*inptr2++);
    cred = Crrtab[cr];
    cgreen = (int)RIGHT_SHIFT(Cbgtab[cb] + Crgtab[cr], SCALEBITS);
    cblue = Cbbtab[cb];
    
    y  = GETJSAMPLE(*inptr0++);
    outptr[RGB_RED] =   range_limit[y + cred];
    outptr[RGB_GREEN] = range_limit[y + cgreen];
    outptr[RGB_BLUE] =  range_limit[y + cblue];
#ifdef RGB_ALPHA
    outptr[RGB_ALPHA] = 0xFF;
#endif
    outptr += RGB_PIXELSIZE;
    y  = GETJSAMPLE(*inptr0++);
    outptr[RGB_RED] =   range_limit[y + cred];
    outptr[RGB_GREEN] = range_limit[y + cgreen];
    outptr[RGB_BLUE] =  range_limit[y + cblue];
#ifdef RGB_ALPHA
    outptr[RGB_ALPHA] = 0xFF;
#endif
    outptr += RGB_PIXELSIZE;
  }
  
  if (cinfo->output_width & 1) {
    cb = GETJSAMPLE(*inptr1);
    cr = GETJSAMPLE(*inptr2);
    cred = Crrtab[cr];
    cgreen = (int)RIGHT_SHIFT(Cbgtab[cb] + Crgtab[cr], SCALEBITS);
    cblue = Cbbtab[cb];
    y  = GETJSAMPLE(*inptr0);
    outptr[RGB_RED] =   range_limit[y + cred];
    outptr[RGB_GREEN] = range_limit[y + cgreen];
    outptr[RGB_BLUE] =  range_limit[y + cblue];
#ifdef RGB_ALPHA
    outptr[RGB_ALPHA] = 0xFF;
#endif
  }
}