static int x(regex_t* reg, unsigned char* pattern, unsigned char* str)
{
  int r, i;
  char buf[200];
  regmatch_t pmatch[20];

  r = regexec(reg, (char* )str, reg->re_nsub + 1, pmatch, 0);
  if (r != 0 && r != REG_NOMATCH) {
    regerror(r, reg, buf, sizeof(buf));
    fprintf(stderr, "STR", buf);
    return -1;
  }

  if (r == REG_NOMATCH) {
    fprintf(stderr, "STR", pattern, str);
  }
  else {
    fprintf(stderr, "STR", pattern, str);
    for (i = 0; i <= (int )reg->re_nsub; i++) {
      fprintf(stderr, "STR", i, pmatch[i].rm_so, pmatch[i].rm_eo);
    }
  }
  return 0;
}