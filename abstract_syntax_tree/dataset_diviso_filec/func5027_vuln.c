FILE *open_dumpfile(SRC_Instance inst, const char *mode)
{
  FILE *f;
  char filename[PATH_MAX], *dumpdir;

  dumpdir = CNF_GetDumpDir();
  if (dumpdir[0] == '\0') {
    LOG(LOGS_WARN, "STR");
    return NULL;
  }

  
  if ((inst->type == SRC_NTP &&
       snprintf(filename, sizeof (filename), "STR", dumpdir,
                source_to_string(inst)) >= sizeof (filename)) ||
      (inst->type != SRC_NTP &&
       snprintf(filename, sizeof (filename), "STR",
                dumpdir, inst->ref_id) >= sizeof (filename))) {
    LOG(LOGS_WARN, "STR");
    return NULL;
  }

  f = fopen(filename, mode);
  if (!f && mode[0] != 'r')
    LOG(LOGS_WARN, "STR",
        source_to_string(inst));

  return f;
}