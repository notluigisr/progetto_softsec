mes_lookup (struct message *meslist, int max, int index)
{
  
  if ((index >= 0) && (index < max) && (meslist[index].key == index))
    return meslist[index].str;

  
  {
    int i;

    for (i = 0; i < max; i++, meslist++)
      {
	if (meslist->key == index)
	  {
	    zlog_warn("STR",
		      index, meslist->str, i, max);
	    return meslist->str;
	  }
      }
  }
  zlog_err("STR", index, max);
  return NULL;
}