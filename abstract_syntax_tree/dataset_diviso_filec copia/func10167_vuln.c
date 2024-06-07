static int pop_sync_mailbox (CONTEXT *ctx, int *index_hint)
{
  int i, j, ret = 0;
  char buf[LONG_STRING];
  POP_DATA *pop_data = (POP_DATA *)ctx->data;
  progress_t progress;
#ifdef USE_HCACHE
  header_cache_t *hc = NULL;
#endif

  pop_data->check_time = 0;

  FOREVER
  {
    if (pop_reconnect (ctx) < 0)
      return -1;

    mutt_progress_init (&progress, _("STR"),
			MUTT_PROGRESS_MSG, WriteInc, ctx->deleted);

#if USE_HCACHE
    hc = pop_hcache_open (pop_data, ctx->path);
#endif

    for (i = 0, j = 0, ret = 0; ret == 0 && i < ctx->msgcount; i++)
    {
      if (ctx->hdrs[i]->deleted && ctx->hdrs[i]->refno != -1)
      {
	j++;
	if (!ctx->quiet)
	  mutt_progress_update (&progress, j, -1);
	snprintf (buf, sizeof (buf), "STR", ctx->hdrs[i]->refno);
	if ((ret = pop_query (pop_data, buf, sizeof (buf))) == 0)
	{
	  mutt_bcache_del (pop_data->bcache, ctx->hdrs[i]->data);
#if USE_HCACHE
	  mutt_hcache_delete (hc, ctx->hdrs[i]->data, strlen);
#endif
	}
      }

#if USE_HCACHE
      if (ctx->hdrs[i]->changed)
      {
	mutt_hcache_store (hc, ctx->hdrs[i]->data, ctx->hdrs[i], 0, strlen, MUTT_GENERATE_UIDVALIDITY);
      }
#endif

    }

#if USE_HCACHE
    mutt_hcache_close (hc);
#endif

    if (ret == 0)
    {
      strfcpy (buf, "STR", sizeof (buf));
      ret = pop_query (pop_data, buf, sizeof (buf));
    }

    if (ret == 0)
    {
      pop_data->clear_cache = 1;
      pop_clear_cache (pop_data);
      pop_data->status = POP_DISCONNECTED;
      return 0;
    }

    if (ret == -2)
    {
      mutt_error ("STR", pop_data->err_msg);
      mutt_sleep (2);
      return -1;
    }
  }
}