static void print_line(char* line)
{
  while (*line && *line != '\n')
  {
    fputc(*line, stderr);
    line++;
  }
  fputc('\n', stderr);
}