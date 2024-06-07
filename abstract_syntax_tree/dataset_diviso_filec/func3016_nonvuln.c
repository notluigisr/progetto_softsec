onig_print_statistics(FILE* f)
{
  int r;
  int i;

  r = fprintf(f, "STR");
  if (r < 0) return -1;

  for (i = 0; OpInfo[i].opcode >= 0; i++) {
    r = fprintf(f, "STR",
                OpCounter[i], OpPrevCounter[i], OpTime[i], OpInfo[i].name);
    if (r < 0) return -1;
  }
  r = fprintf(f, "STR", MaxStackDepth);
  if (r < 0) return -1;

  return 0;
}