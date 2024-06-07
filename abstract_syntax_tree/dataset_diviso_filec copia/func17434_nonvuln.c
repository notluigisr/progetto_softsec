extern int main(int argc, char* argv[])
{
  int r;
  char buf[200];
  regex_t reg;
  UChar* pattern;

  
  pattern = (UChar* )"STR";
  r = regcomp(&reg, (char* )pattern, REG_EXTENDED);
  if (r) {
    regerror(r, &reg, buf, sizeof(buf));
    fprintf(stderr, "STR", buf);
    return -1;
  }
  x(&reg, pattern, (UChar* )"STR");

  
  pattern = (UChar* )"STR";
  r = regcomp(&reg, (char* )pattern, 0);
  if (r) {
    regerror(r, &reg, buf, sizeof(buf));
    fprintf(stderr, "STR", buf);
    return -1;
  }
  x(&reg, pattern, (UChar* )"STR");

  
  pattern = (UChar* )"STR";
  r = regcomp(&reg, (char* )pattern, 0);
  if (r) {
    regerror(r, &reg, buf, sizeof(buf));
    fprintf(stderr, "STR", buf);
    return -1;
  }
  x(&reg, pattern, (UChar* )"STR");

  
  onig_set_default_syntax(ONIG_SYNTAX_POSIX_EXTENDED);
  pattern = (UChar* )"STR";
  r = regcomp(&reg, (char* )pattern, REG_EXTENDED);
  if (r) {
    regerror(r, &reg, buf, sizeof(buf));
    fprintf(stderr, "STR", buf);
    return -1;
  }
  x(&reg, pattern, (UChar* )"STR");

  pattern = (UChar* )"STR";
  r = regcomp(&reg, (char* )pattern, REG_EXTENDED | REG_NEWLINE);
  if (r) {
    regerror(r, &reg, buf, sizeof(buf));
    fprintf(stderr, "STR", buf);
    return -1;
  }
  x(&reg, pattern, (UChar* )"STR");

  regfree(&reg);
  return 0;
}