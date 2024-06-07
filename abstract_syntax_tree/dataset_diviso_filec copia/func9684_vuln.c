SRC_RemoveDumpFiles(void)
{
  char pattern[PATH_MAX], name[64], *dumpdir, *s;
  IPAddr ip_addr;
  glob_t gl;
  size_t i;

  dumpdir = CNF_GetDumpDir();
  if (dumpdir[0] == '\0' ||
      snprintf(pattern, sizeof (pattern), "STR", dumpdir) >= sizeof (pattern))
    return;

  if (glob(pattern, 0, NULL, &gl))
    return;

  for (i = 0; i < gl.gl_pathc; i++) {
    s = strrchr(gl.gl_pathv[i], '/');
    if (!s || snprintf(name, sizeof (name), "STR", s + 1) >= sizeof (name))
      continue;

    
    if (strlen(name) < 4)
      continue;
    name[strlen(name) - 4] = '\0';

    
    if (strncmp(name, "STR", 6) && !UTI_StringToIP(name, &ip_addr))
      continue;

    DEBUG_LOG("STR", gl.gl_pathv[i]);
    unlink(gl.gl_pathv[i]);
  }

  globfree(&gl);
}