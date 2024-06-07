static bool imap_matchresp(const char *line, size_t len, const char *cmd)
{
  const char *end = line + len;
  size_t cmd_len = strlen(cmd);

  
  line += 2;

  
  if(line < end && ISDIGIT(*line)) {
    
    do
      line++;
    while(line < end && ISDIGIT(*line));

    
    if(line == end || *line != ' ')
      return FALSE;

    line++;
  }

  
  if(line + cmd_len <= end && strncasecompare(line, cmd, cmd_len) &&
     (line[cmd_len] == ' ' || line + cmd_len + 2 == end))
    return TRUE;

  return FALSE;
}