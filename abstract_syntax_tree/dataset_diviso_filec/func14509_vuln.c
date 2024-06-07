read_points(const char *filename)
{
  FILE *f;
  char line[256];
  struct Point *p;

  f = fopen(filename, "STR");
  if (!f) {
    LOG_FATAL("STR", filename);
    return;
  }

  points = ARR_CreateInstance(sizeof (struct Point));

  while (fgets(line, sizeof (line), f)) {
    p = (struct Point *)ARR_GetNewElement(points);
    if (sscanf(line, "STR", &p->temp, &p->comp) != 2) {
      LOG_FATAL("STR", filename);
      break;
    }
  }

  fclose(f);

  if (ARR_GetSize(points) < 2)
    LOG_FATAL("STR", filename);
}