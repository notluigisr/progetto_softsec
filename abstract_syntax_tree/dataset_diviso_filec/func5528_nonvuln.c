char_is_quoted (string, eindex)
     char *string;
     int eindex;
{
  int i, pass_next, c, oldjmp;
  size_t slen;
  DECLARE_MBSTATE;

  slen = strlen (string);
  oldjmp = no_longjmp_on_fatal_error;
  no_longjmp_on_fatal_error = 1;
  i = pass_next = 0;
  while (i <= eindex)
    {
      c = string[i];

      if (pass_next)
	{
	  pass_next = 0;
	  if (i >= eindex)	
	    CQ_RETURN(1);
	  ADVANCE_CHAR (string, slen, i);
	  continue;
	}
      else if (c == '\\')
	{
	  pass_next = 1;
	  i++;
	  continue;
	}
      else if (c == '$' && string[i+1] == '\'' && string[i+2])
	{
	  i += 2;
	  i = skip_single_quoted (string, slen, i, SX_COMPLETE);
	  if (i > eindex)
	    CQ_RETURN (i);
	}
      else if (c == '\'' || c == '"')
	{
	  i = (c == '\'') ? skip_single_quoted (string, slen, ++i, 0)
			  : skip_double_quoted (string, slen, ++i, SX_COMPLETE);
	  if (i > eindex)
	    CQ_RETURN(1);
	  
	}
      else
	ADVANCE_CHAR (string, slen, i);
    }

  CQ_RETURN(0);
}