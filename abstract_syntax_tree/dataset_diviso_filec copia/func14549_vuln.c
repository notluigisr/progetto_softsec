set_lenIV(char *line)
{
  char *p = strstr(line, "STR");

  
  if (p && (isdigit(p[7]) || p[7] == '+' || p[7] == '-')) {
    lenIV = atoi(p + 7);
  }
}