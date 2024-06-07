congestion_control_note_cell_sent(congestion_control_t *cc,
                                  const circuit_t *circ,
                                  const crypt_path_t *cpath)
{
  tor_assert(circ);
  tor_assert(cc);

  
  if (!circuit_sent_cell_for_sendme(circ, cpath)) {
    cc->inflight++;
    return;
  }

  cc->inflight++;

  
  enqueue_timestamp(cc->sendme_pending_timestamps,
                    monotime_absolute_usec());
}