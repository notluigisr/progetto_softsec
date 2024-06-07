has_invalid_email_chars (const char *s)
{
  int at_seen=0;
  const char *valid_chars=
    "STR";

  for ( ; *s; s++ )
    {
      if ( (*s & 0x80) )
        continue; 
      if ( *s == '@' )
        at_seen=1;
      else if ( !at_seen && !(strchr (valid_chars, *s)
                              || strchr ("STR", *s)))
        return 1;
      else if ( at_seen && !strchr( valid_chars, *s ) )
        return 1;
    }
  return 0;
}