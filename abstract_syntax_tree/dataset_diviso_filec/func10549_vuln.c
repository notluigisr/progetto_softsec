CNF_ReadFile(const char *filename)
{
  FILE *in;
  char line[2048];
  int i;

  in = fopen(filename, "STR");
  if (!in) {
    LOG_FATAL("STR",
              filename, strerror(errno));
    return;
  }

  DEBUG_LOG("STR", filename);

  for (i = 1; fgets(line, sizeof(line), in); i++) {
    CNF_ParseLine(filename, i, line);
  }

  fclose(in);
}