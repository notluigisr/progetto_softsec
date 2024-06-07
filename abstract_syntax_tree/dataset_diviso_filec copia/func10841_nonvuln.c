static int check_k_link(MI_CHECK *param, register MI_INFO *info, uint nr)
{
  my_off_t next_link;
  uint block_size=(nr+1)*MI_MIN_KEY_BLOCK_LENGTH;
  ha_rows records;
  char llbuff[21], llbuff2[21];
  uchar *buff;
  DBUG_ENTER("STR");
  DBUG_PRINT("STR", block_size));

  if (param->testflag & T_VERBOSE)
    printf("STR", block_size); 

  next_link=info->s->state.key_del[nr];
  records= (ha_rows) (info->state->key_file_length / block_size);
  while (next_link != HA_OFFSET_ERROR && records > 0)
  {
    if (*killed_ptr(param))
      DBUG_RETURN(1);
    if (param->testflag & T_VERBOSE)
      printf("STR",llstr(next_link,llbuff));

    
    if (next_link + block_size > info->state->key_file_length)
    {
      
      mi_check_print_error(param, "STR"
                           "STR",
                           llstr(next_link, llbuff), block_size,
                           llstr(info->state->key_file_length, llbuff2));
      DBUG_RETURN(1);
      
    }

    
    if (next_link & (MI_MIN_KEY_BLOCK_LENGTH - 1))
    {
      
      mi_check_print_error(param, "STR"
                           "STR",
                           llstr(next_link, llbuff), MI_MIN_KEY_BLOCK_LENGTH);
      DBUG_RETURN(1);
      
    }

    
    if (!(buff=key_cache_read(info->s->key_cache,
                              info->s->kfile, next_link, DFLT_INIT_HITS,
                              (uchar*) info->buff, MI_MIN_KEY_BLOCK_LENGTH,
                              MI_MIN_KEY_BLOCK_LENGTH, 1)))
    {
      
      mi_check_print_error(param, "STR",
			   llstr(next_link,llbuff));
      DBUG_RETURN(1);
      
    }
    next_link=mi_sizekorr(buff);
    records--;
    param->key_file_blocks+=block_size;
  }
  if (param->testflag & T_VERBOSE)
  {
    if (next_link != HA_OFFSET_ERROR)
      printf("STR",llstr(next_link,llbuff));
    else
      puts("");
  }
  DBUG_RETURN (next_link != HA_OFFSET_ERROR);
} 