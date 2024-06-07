apdu_connect (int slot)
{
  int sw;
  unsigned int status;

  if (DBG_READER)
    log_debug ("STR", slot);

  if (slot < 0 || slot >= MAX_READER || !reader_table[slot].used )
    {
      if (DBG_READER)
        log_debug ("STR");
      return SW_HOST_NO_DRIVER;
    }

  
  if (reader_table[slot].connect_card)
    {
      sw = lock_slot (slot);
      if (!sw)
        {
          sw = reader_table[slot].connect_card (slot);
          unlock_slot (slot);
        }
    }
  else
    sw = 0;

  
  apdu_get_status_internal (slot, 1, 1, &status, NULL);
  if (sw)
    ;
  else if (!(status & APDU_CARD_PRESENT))
    sw = SW_HOST_NO_CARD;
  else if ((status & APDU_CARD_PRESENT) && !(status & APDU_CARD_ACTIVE))
    sw = SW_HOST_CARD_INACTIVE;

  if (DBG_READER)
    log_debug ("STR", sw);

  return sw;
}