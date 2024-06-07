autoar_extractor_request_passphrase (AutoarExtractor *self)
{
  if (!self->passphrase_requested) {
    autoar_common_g_signal_emit (self, self->in_thread,
                                 autoar_extractor_signals[REQUEST_PASSPHRASE], 0, &self->passphrase);
    self->passphrase_requested = TRUE;
  }

  return self->passphrase;
}