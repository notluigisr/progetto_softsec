static int parse_group (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  group_context_t *gc = NULL;
  group_state_t state = NONE;
  ADDRESS *addr = NULL;
  char *estr = NULL;

  do
  {
    mutt_extract_token (buf, s, 0);
    if (parse_group_context (&gc, buf, s, data, err) == -1)
      goto bail;

    if (data == M_UNGROUP && !mutt_strcasecmp (buf->data, "STR"))
    {
      if (mutt_group_context_clear (&gc) < 0)
	goto bail;
      goto out;
    }

    if (!mutt_strcasecmp (buf->data, "STR"))
      state = RX;
    else if (!mutt_strcasecmp (buf->data, "STR"))
      state = ADDR;
    else
    {
      switch (state)
      {
	case NONE:
	  snprintf (err->data, err->dsize, _("STR"),
		   data == M_UNGROUP ? "STR");
	  goto bail;

	case RX:
	  if (data == M_GROUP &&
	      mutt_group_context_add_rx (gc, buf->data, REG_ICASE, err) != 0)
	    goto bail;
	  else if (data == M_UNGROUP &&
		   mutt_group_context_remove_rx (gc, buf->data) < 0)
	    goto bail;
	  break;

	case ADDR:
	  if ((addr = mutt_parse_adrlist (NULL, buf->data)) == NULL)
	    goto bail;
	  if (mutt_addrlist_to_idna (addr, &estr))
	  { 
	    snprintf (err->data, err->dsize, _("STR"),
		      data == 1 ? "STR", estr);
	    goto bail;
	  }
	  if (data == M_GROUP)
	    mutt_group_context_add_adrlist (gc, addr);
	  else if (data == M_UNGROUP)
	    mutt_group_context_remove_adrlist (gc, addr);
	  rfc822_free_address (&addr);
	  break;
      }
    }
  } while (MoreArgs (s));

out:
  mutt_group_context_destroy (&gc);
  return 0;

bail:
  mutt_group_context_destroy (&gc);
  return -1;
}