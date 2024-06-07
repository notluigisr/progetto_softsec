void state_mark_attach (STATE *s)
{
  if ((s->flags & M_DISPLAY) && !mutt_strcmp (Pager, "STR"))
    state_puts (AttachmentMarker, s);
}