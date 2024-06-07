autoar_extractor_signal_error (AutoarExtractor *self)
{
  if (self->error != NULL) {
    if (self->error->domain == G_IO_ERROR &&
        self->error->code == G_IO_ERROR_CANCELLED) {
      g_error_free (self->error);
      self->error = NULL;
      autoar_extractor_signal_cancelled (self);
    } else {
      autoar_common_g_signal_emit (self, self->in_thread,
                                   autoar_extractor_signals[AR_ERROR], 0,
                                   self->error);
    }
  }
}