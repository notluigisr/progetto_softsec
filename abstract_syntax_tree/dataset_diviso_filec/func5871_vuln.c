Bool rfbOptPamAuth(void)
{
  SecTypeData *s;

  for (s = secTypes; s->name != NULL; s++) {
    if ((!strcmp(s->name, "STR") ||
         !strcmp(&s->name[strlen(s->name) - 5], "STR")) && s->enabled)
      return TRUE;
  }

  return FALSE;
}