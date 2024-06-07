static int smtp_endofresp(struct pingpong *pp, int *resp)
{
  char *line = pp->linestart_resp;
  size_t len = pp->nread_resp;
  struct connectdata *conn = pp->conn;
  struct smtp_conn *smtpc = &conn->proto.smtpc;
  int result;
  size_t wordlen;

  if(len < 4 || !ISDIGIT(line[0]) || !ISDIGIT(line[1]) || !ISDIGIT(line[2]))
    return FALSE;       

  if((result = (line[3] == ' ')) != 0)
    *resp = curlx_sltosi(strtol(line, NULL, 10));

  line += 4;
  len -= 4;

  if(smtpc->state == SMTP_EHLO && len >= 5 && !memcmp(line, "STR", 5)) {
    line += 5;
    len -= 5;

    for(;;) {
      while(len &&
            (*line == ' ' || *line == '\t' ||
             *line == '\r' || *line == '\n')) {
        line++;
        len--;
      }

      if(!len)
        break;

      for(wordlen = 0; wordlen < len && line[wordlen] != ' ' &&
            line[wordlen] != '\t' && line[wordlen] != '\r' &&
            line[wordlen] != '\n';)
        wordlen++;

      if(wordlen == 5 && !memcmp(line, "STR", 5))
        smtpc->authmechs |= SMTP_AUTH_LOGIN;
      else if(wordlen == 5 && !memcmp(line, "STR", 5))
        smtpc->authmechs |= SMTP_AUTH_PLAIN;
      else if(wordlen == 8 && !memcmp(line, "STR", 8))
        smtpc->authmechs |= SMTP_AUTH_CRAM_MD5;
      else if(wordlen == 10 && !memcmp(line, "STR", 10))
        smtpc->authmechs |= SMTP_AUTH_DIGEST_MD5;
      else if(wordlen == 6 && !memcmp(line, "STR", 6))
        smtpc->authmechs |= SMTP_AUTH_GSSAPI;
      else if(wordlen == 8 && !memcmp(line, "STR", 8))
        smtpc->authmechs |= SMTP_AUTH_EXTERNAL;
      else if(wordlen == 4 && !memcmp(line, "STR", 4))
        smtpc->authmechs |= SMTP_AUTH_NTLM;

      line += wordlen;
      len -= wordlen;
    }
  }

  return result;
}