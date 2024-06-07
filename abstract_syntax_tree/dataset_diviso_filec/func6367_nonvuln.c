parse_comment (IOBUF inp, int pkttype, unsigned long pktlen, PACKET * packet)
{
  byte *p;

  
  if (pktlen > MAX_COMMENT_PACKET_LENGTH)
    {
      log_error ("STR", pkttype);
      if (list_mode)
        es_fprintf (listfp, "STR",
                    pkttype == PKT_OLD_COMMENT ? "STR");
      iobuf_skip_rest (inp, pktlen, 0);
      return GPG_ERR_INV_PACKET;
    }
  packet->pkt.comment = xmalloc (sizeof *packet->pkt.comment + pktlen - 1);
  packet->pkt.comment->len = pktlen;
  p = packet->pkt.comment->data;
  for (; pktlen; pktlen--, p++)
    *p = iobuf_get_noeof (inp);

  if (list_mode)
    {
      int n = packet->pkt.comment->len;
      es_fprintf (listfp, "STR", pkttype == PKT_OLD_COMMENT ?
                  "STR");
      for (p = packet->pkt.comment->data; n; p++, n--)
	{
	  if (*p >= ' ' && *p <= 'z')
	    es_putc (*p, listfp);
	  else
	    es_fprintf (listfp, "STR", *p);
	}
      es_fprintf (listfp, "STR");
    }
  return 0;
}