void tee_puts(const char *s, FILE *file)
{
  tee_fputs(s, file);
  tee_putc('\n', file);
}