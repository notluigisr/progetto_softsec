slew_sources(struct timespec *raw, struct timespec *cooked, double dfreq,
             double doffset, LCL_ChangeType change_type, void *anything)
{
  int i;

  for (i=0; i<n_sources; i++) {
    if (change_type == LCL_ChangeUnknownStep) {
      SST_ResetInstance(sources[i]->stats);
    } else {
      SST_SlewSamples(sources[i]->stats, cooked, dfreq, doffset);
    }
  }

  if (change_type == LCL_ChangeUnknownStep) {
    
    SRC_SelectSource(NULL);
  }
}