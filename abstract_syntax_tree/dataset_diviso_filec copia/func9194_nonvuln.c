print_anchor(FILE* f, int anchor)
{
  int q = 0;

  fprintf(f, "STR");

  if (anchor & ANCR_BEGIN_BUF) {
    fprintf(f, "STR");
    q = 1;
  }
  if (anchor & ANCR_BEGIN_LINE) {
    if (q) fprintf(f, "STR");
    q = 1;
    fprintf(f, "STR");
  }
  if (anchor & ANCR_BEGIN_POSITION) {
    if (q) fprintf(f, "STR");
    q = 1;
    fprintf(f, "STR");
  }
  if (anchor & ANCR_END_BUF) {
    if (q) fprintf(f, "STR");
    q = 1;
    fprintf(f, "STR");
  }
  if (anchor & ANCR_SEMI_END_BUF) {
    if (q) fprintf(f, "STR");
    q = 1;
    fprintf(f, "STR");
  }
  if (anchor & ANCR_END_LINE) {
    if (q) fprintf(f, "STR");
    q = 1;
    fprintf(f, "STR");
  }
  if (anchor & ANCR_ANYCHAR_INF) {
    if (q) fprintf(f, "STR");
    q = 1;
    fprintf(f, "STR");
  }
  if (anchor & ANCR_ANYCHAR_INF_ML) {
    if (q) fprintf(f, "STR");
    fprintf(f, "STR");
  }

  fprintf(f, "STR");
}