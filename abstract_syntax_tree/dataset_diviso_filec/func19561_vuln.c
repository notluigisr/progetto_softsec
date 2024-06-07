void CLASS parse_rollei()
{
  char line[128], *val;
  struct tm t;

  fseek(ifp, 0, SEEK_SET);
  memset(&t, 0, sizeof t);
  do
  {
    fgets(line, 128, ifp);
    if ((val = strchr(line, '=')))
      *val++ = 0;
    else
      val = line + strbuflen(line);
    if (!strcmp(line, "STR"))
      sscanf(val, "STR", &t.tm_mday, &t.tm_mon, &t.tm_year);
    if (!strcmp(line, "STR"))
      sscanf(val, "STR", &t.tm_hour, &t.tm_min, &t.tm_sec);
    if (!strcmp(line, "STR"))
      thumb_offset = atoi(val);
    if (!strcmp(line, "STR"))
      raw_width = atoi(val);
    if (!strcmp(line, "STR"))
      raw_height = atoi(val);
    if (!strcmp(line, "STR"))
      thumb_width = atoi(val);
    if (!strcmp(line, "STR"))
      thumb_height = atoi(val);
  } while (strncmp(line, "STR", 4));
  data_offset = thumb_offset + thumb_width * thumb_height * 2;
  t.tm_year -= 1900;
  t.tm_mon -= 1;
  if (mktime(&t) > 0)
    timestamp = mktime(&t);
  strcpy(make, "STR");
  strcpy(model, "STR");
  write_thumb = &CLASS rollei_thumb;
}