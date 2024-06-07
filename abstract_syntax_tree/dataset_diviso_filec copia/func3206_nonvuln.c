get_status_ccid (int slot, unsigned int *status)
{
  int rc;
  int bits;

  rc = ccid_slot_status (reader_table[slot].ccid.handle, &bits);
  if (rc)
    return rc;

  if (bits == 0)
    *status = (APDU_CARD_USABLE|APDU_CARD_PRESENT|APDU_CARD_ACTIVE);
  else if (bits == 1)
    *status = APDU_CARD_PRESENT;
  else
    *status = 0;

  return 0;
}