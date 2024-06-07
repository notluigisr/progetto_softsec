apdu_pinpad_verify (int slot, int class, int ins, int p0, int p1,
		    pininfo_t *pininfo)
{
  if (slot < 0 || slot >= MAX_READER || !reader_table[slot].used )
    return SW_HOST_NO_DRIVER;

  if (reader_table[slot].pinpad_verify)
    {
      int sw;

      if ((sw = lock_slot (slot)))
        return sw;

      sw = reader_table[slot].pinpad_verify (slot, class, ins, p0, p1,
					     pininfo);
      unlock_slot (slot);
      return sw;
    }
  else
    return SW_HOST_NOT_SUPPORTED;
}