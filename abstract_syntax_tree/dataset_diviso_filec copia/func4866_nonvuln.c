schedule_fb_drift(struct timespec *now)
{
  int i, c, secs;
  double unsynchronised;
  struct timespec when;

  if (fb_drift_timeout_id)
    return; 

  unsynchronised = UTI_DiffTimespecsToDouble(now, &last_ref_update);

  for (c = secs = 0, i = fb_drift_min; i <= fb_drift_max; i++) {
    secs = 1 << i;

    if (fb_drifts[i - fb_drift_min].secs < secs)
      continue;

    if (unsynchronised < secs && i > next_fb_drift)
      break;

    c = i;
  }

  if (c > next_fb_drift) {
    LCL_SetAbsoluteFrequency(fb_drifts[c - fb_drift_min].freq);
    next_fb_drift = c;
    DEBUG_LOG("STR", c);
  }

  if (i <= fb_drift_max) {
    next_fb_drift = i;
    UTI_AddDoubleToTimespec(now, secs - unsynchronised, &when);
    fb_drift_timeout_id = SCH_AddTimeout(&when, fb_drift_timeout, NULL);
    DEBUG_LOG("STR", i);
  }
}