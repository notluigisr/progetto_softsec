expand_arith_string (string, quoted)
     char *string;
     int quoted;
{
  WORD_DESC td;
  WORD_LIST *list, *tlist;
  size_t slen;
  int i, saw_quote;
  char *ret;
  DECLARE_MBSTATE;

  
  slen = (MB_CUR_MAX > 1) ? strlen (string) : 0;
  i = saw_quote = 0;
  while (string[i])
    {
      if (EXP_CHAR (string[i]))
	break;
      else if (string[i] == '\'' || string[i] == '\\' || string[i] == '"')
	saw_quote = 1;
      ADVANCE_CHAR (string, slen, i);
    }

  if (string[i])
    {
      
      td.flags = W_NOPROCSUB;	
      td.word = savestring (string);
      list = call_expand_word_internal (&td, quoted, 0, (int *)NULL, (int *)NULL);
      
      if (list)
	{
	  tlist = word_list_split (list);
	  dispose_words (list);
	  list = tlist;
	  if (list)
	    dequote_list (list);
	}
      
      if (list)
	{
	  ret = string_list (list);
	  dispose_words (list);
	}
      else
	ret = (char *)NULL;
      FREE (td.word);
    }
  else if (saw_quote && (quoted & Q_ARITH))
    ret = string_quote_removal (string, quoted);
  else if (saw_quote && ((quoted & (Q_HERE_DOCUMENT|Q_DOUBLE_QUOTES)) == 0))
    ret = string_quote_removal (string, quoted);
  else
    ret = savestring (string);

  return ret;
}