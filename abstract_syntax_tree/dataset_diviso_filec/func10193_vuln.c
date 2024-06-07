SRC_DumpSources(void)
{
  FILE *out;
  int i;

  for (i = 0; i < n_sources; i++) {
    out = open_dumpfile(sources[i], "STR");
    if (!out)
      continue;
    SST_SaveToFile(sources[i]->stats, out);
    fclose(out);
  }
}