static gboolean grow_buffer (struct bmp_progressive_state *State,
                             GError **error)
{
  guchar *tmp;

  if (State->BufferSize == 0) {
    g_set_error_literal (error,
                         GDK_PIXBUF_ERROR,
                         GDK_PIXBUF_ERROR_CORRUPT_IMAGE,
                         _("STR"));
    State->read_state = READ_STATE_ERROR;
    return FALSE;
  }

  tmp = g_try_realloc (State->buff, State->BufferSize);

  if (!tmp) {
    g_set_error_literal (error,
                         GDK_PIXBUF_ERROR,
                         GDK_PIXBUF_ERROR_INSUFFICIENT_MEMORY,
                         _("STR"));
    State->read_state = READ_STATE_ERROR;
    return FALSE;
  }

  State->buff = tmp;
  return TRUE;
}