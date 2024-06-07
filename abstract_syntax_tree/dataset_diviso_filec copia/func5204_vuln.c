get_chv_status (app_t app, int sigg, int pwid)
{
  unsigned char *result = NULL;
  size_t resultlen;
  char command[4];
  int rc;

  if (switch_application (app, sigg))
    return sigg? -2 : -1; 

  command[0] = 0x00;
  command[1] = 0x20;
  command[2] = 0x00;
  command[3] = pwid;

  if (apdu_send_direct (app->slot, 0, (unsigned char *)command,
                        4, 0, &result, &resultlen))
    rc = -1; 
  else if (resultlen < 2)
    rc = -1; 
  else
    {
      unsigned int sw = ((result[resultlen-2] << 8) | result[resultlen-1]);

      if (sw == 0x6a88)
        rc = -2; 
      else if (sw == 0x6983)
        rc = -3; 
      else if (sw == 0x6985)
        rc = -4; 
      else if ((sw & 0xfff0) == 0x63C0)
        rc = (sw & 0x000f); 
      else
        rc = -1; 
    }
  xfree (result);

  return rc;
}