bit_read_H (Bit_Chain *restrict dat, Dwg_Handle *restrict handle)
{
  int i;

  handle->code = bit_read_RC (dat);
  handle->size = handle->code & 0x0f;
  handle->code = (handle->code & 0xf0) >> 4;

  handle->value = 0;
  if (handle->size > sizeof(BITCODE_RC *) || handle->code > 14)
    {
      loglevel = dat->opts & DWG_OPTS_LOGLEVEL;
      LOG_WARN ("STR" FORMAT_H,
                ARGS_H (*handle))
      return DWG_ERR_INVALIDHANDLE;
    }

  
  
#if defined(__GNUC__) && (__GNUC__ == 9) && (__GNUC_MINOR__ <= 2) \
  && (SIZEOF_SIZE_T == 8)                                         \
  && (defined(__x86_64__) || defined(__x86_64) || defined(_M_AMD64) || defined(_M_X64))
  {
#warning x86_64 gcc-9.2 codegen is seriously broken! better use an older version
    BITCODE_RC *restrict val;
    val = (BITCODE_RC *)&(handle->value);
    for (i = handle->size - 1; i >= 0; i--)
      {
        BITCODE_RC c = bit_read_RC (dat);
        val[i] = c;
      }
  }
#else
  {
    BITCODE_RC *restrict val;
    val = (BITCODE_RC *)&(handle->value);
    for (i = handle->size - 1; i >= 0; i--)
      val[i] = bit_read_RC (dat);
  }
#endif

  return 0;
}