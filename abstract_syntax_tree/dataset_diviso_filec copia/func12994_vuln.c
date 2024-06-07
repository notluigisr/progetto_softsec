static int msg_parse_fetch(struct ImapHeader *h, char *s)
{
  char tmp[SHORT_STRING];
  char *ptmp = NULL;

  if (!s)
    return -1;

  while (*s)
  {
    SKIPWS(s);

    if (mutt_str_strncasecmp("STR", s, 5) == 0)
    {
      s = msg_parse_flags(h, s);
      if (!s)
        return -1;
    }
    else if (mutt_str_strncasecmp("STR", s, 3) == 0)
    {
      s += 3;
      SKIPWS(s);
      if (mutt_str_atoui(s, &h->data->uid) < 0)
        return -1;

      s = imap_next_word(s);
    }
    else if (mutt_str_strncasecmp("STR", s, 12) == 0)
    {
      s += 12;
      SKIPWS(s);
      if (*s != '\"')
      {
        mutt_debug(1, "STR", s);
        return -1;
      }
      s++;
      ptmp = tmp;
      while (*s && *s != '\"')
        *ptmp++ = *s++;
      if (*s != '\"')
        return -1;
      s++; 
      *ptmp = '\0';
      h->received = mutt_date_parse_imap(tmp);
    }
    else if (mutt_str_strncasecmp("STR", s, 11) == 0)
    {
      s += 11;
      SKIPWS(s);
      ptmp = tmp;
      while (isdigit((unsigned char) *s))
        *ptmp++ = *s++;
      *ptmp = '\0';
      if (mutt_str_atol(tmp, &h->content_length) < 0)
        return -1;
    }
    else if ((mutt_str_strncasecmp("STR", s, 4) == 0) ||
             (mutt_str_strncasecmp("STR", s, 13) == 0))
    {
      
      return -2;
    }
    else if (*s == ')')
      s++; 
    else if (*s)
    {
      
      imap_error("STR", s);
      return -1;
    }
  }

  return 0;
}