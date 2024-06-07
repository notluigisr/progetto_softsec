dat_read_file (Bit_Chain *restrict dat, FILE *restrict fp,
               const char *restrict filename)
{
  size_t size;
  if (!dat->size && fp)
    {
      struct stat attrib;
      int fd = fileno (fp);
      if (fd >= 0 && !fstat (fd, &attrib))
        dat->size = attrib.st_size;
    }
  dat->chain = (unsigned char *)calloc (1, dat->size + 1);
  if (!dat->chain)
    {
      loglevel = dat->opts & DWG_OPTS_LOGLEVEL;
      LOG_ERROR ("STR")
      fclose (fp);
      return DWG_ERR_OUTOFMEM;
    }

  size = fread (dat->chain, sizeof (char), dat->size, fp);
  if (size != dat->size)
    {
      loglevel = dat->opts & DWG_OPTS_LOGLEVEL;
      LOG_ERROR ("STR",
                 (long unsigned int)size, dat->size, filename)
      fclose (fp);
      free (dat->chain);
      dat->chain = NULL;
      dat->size = 0;
      return DWG_ERR_IOERROR;
    }
  dat->chain[dat->size] = '\0';  
  return 0;
}