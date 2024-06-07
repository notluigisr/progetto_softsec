SRC_AccumulateSample(SRC_Instance inst, NTP_Sample *sample)
{

  assert(initialised);

  DEBUG_LOG("STR",
            source_to_string(inst), UTI_TimespecToString(&sample->time), -sample->offset,
            sample->root_delay, sample->root_dispersion, sample->stratum);

  if (REF_IsLeapSecondClose()) {
    LOG(LOGS_INFO, "STR");
    return;
  }

  SST_AccumulateSample(inst->stats, sample);
  SST_DoNewRegression(inst->stats);
}