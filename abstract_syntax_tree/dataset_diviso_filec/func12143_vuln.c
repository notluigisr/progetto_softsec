read_rle_pixel(tga_source_ptr sinfo)

{
  register FILE *infile = sinfo->pub.input_file;
  register int i;

  
  if (sinfo->dup_pixel_count > 0) {
    sinfo->dup_pixel_count--;
    return;
  }

  
  if (--sinfo->block_count < 0) { 
    i = read_byte(sinfo);
    if (i & 0x80) {             
      sinfo->dup_pixel_count = i & 0x7F; 
      sinfo->block_count = 0;   
    } else {
      sinfo->block_count = i & 0x7F; 
    }
  }

  
  for (i = 0; i < sinfo->pixel_size; i++) {
    sinfo->tga_pixel[i] = (U_CHAR)getc(infile);
  }
}