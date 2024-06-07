dat_read_stream (Bit_Chain *restrict dat, FILE *restrict fp)
{
  size_t size = 0;
  loglevel = dat->opts & DWG_OPTS_LOGLEVEL;

  do
    {
      if (dat->chain)
        dat->chain = (unsigned char *)realloc (dat->chain, dat->size + 4096);
      else
        {
          dat->chain = (unsigned char *)calloc (1, 4096);
          dat->size = 0;
        }
      if (!dat->chain)
        {
          LOG_ERROR ("STR");
          fclose (fp);
          return DWG_ERR_OUTOFMEM;
        }
      size = fread (&dat->chain[dat->size], sizeof (char), 4096, fp);
      dat->size += size;
    }
  while (size == 4096);

  if (dat->size == 0)
    {
      LOG_ERROR ("STR",
                 (long unsigned int)size, dat->size);
      fclose (fp);
      free (dat->chain);
      dat->chain = NULL;
      return DWG_ERR_IOERROR;
    }

  
  size = dat->size & 0xfff;
  if (size)
    memset (&dat->chain[dat->size], 0, 0xfff - size);
  dat->chain = (unsigned char *)realloc (dat->chain, dat->size + 1);
  
  dat->chain[dat->size] = '\0';
  return 0;
}