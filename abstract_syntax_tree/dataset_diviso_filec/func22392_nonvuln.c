flatpak_remote_state_ensure_summary (FlatpakRemoteState *self,
                                     GError            **error)
{
  if (self->summary == NULL)
    return flatpak_fail_error (error, FLATPAK_ERROR_INVALID_DATA, _("STR"), self->remote_name,
                         self->summary_fetch_error != NULL ? self->summary_fetch_error->message : "STR");

  return TRUE;
}