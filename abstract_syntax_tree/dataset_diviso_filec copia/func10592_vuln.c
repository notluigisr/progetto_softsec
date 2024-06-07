SRC_ReloadSources(void)
{
  FILE *in;
  int i;

  for (i = 0; i < n_sources; i++) {
    in = open_dumpfile(sources[i], "STR");
    if (!in)
      continue;
    if (!SST_LoadFromFile(sources[i]->stats, in))
      LOG(LOGS_WARN, "STR",
          source_to_string(sources[i]));
    else
      LOG(LOGS_INFO, "STR",
          source_to_string(sources[i]));
    fclose(in);
  }
}