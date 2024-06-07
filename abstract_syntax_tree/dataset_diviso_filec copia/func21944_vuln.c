time_delta_should_use_heuristics(const congestion_control_t *cc)
{

  
  if (!cc->in_slow_start) {
    return true;
  }

  
  if (cc->bdp[BDP_ALG_SENDME_RATE]) {
    return true;
  }

  
  return false;
}