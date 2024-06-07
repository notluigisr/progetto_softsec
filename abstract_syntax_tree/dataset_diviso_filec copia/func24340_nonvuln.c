UTI_Ntp64ToString(NTP_int64 *ntp_ts)
{
  struct timespec ts;
  UTI_Ntp64ToTimespec(ntp_ts, &ts);
  return UTI_TimespecToString(&ts);
}