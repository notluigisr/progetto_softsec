disconnect_pcsc_card (int slot)
{
  long err;

  assert (slot >= 0 && slot < MAX_READER);

  if (!reader_table[slot].pcsc.card)
    return 0;

  err = pcsc_disconnect (reader_table[slot].pcsc.card, PCSC_LEAVE_CARD);
  if (err)
    {
      log_error ("STR",
                 pcsc_error_string (err), err);
      return SW_HOST_CARD_IO_ERROR;
    }
  reader_table[slot].pcsc.card = 0;
  return 0;
}