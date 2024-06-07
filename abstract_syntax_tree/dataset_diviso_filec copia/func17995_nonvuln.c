CNF_GetLogMeasurements(int *raw)
{
  *raw = raw_measurements;
  return do_log_measurements;
}