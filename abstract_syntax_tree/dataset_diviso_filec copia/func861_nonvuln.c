libarchive_read_skip_cb (struct archive *ar_read,
                         void           *client_data,
                         gint64          request)
{
  AutoarExtractor *self;
  GSeekable *seekable;
  off_t old_offset, new_offset;

  g_debug ("STR");

  self = AUTOAR_EXTRACTOR (client_data);
  seekable = (GSeekable*)(self->istream);
  if (self->error != NULL || self->istream == NULL) {
    return -1;
  }

  old_offset = g_seekable_tell (seekable);
  new_offset = libarchive_read_seek_cb (ar_read, client_data, request, SEEK_CUR);
  if (new_offset > old_offset)
    return (new_offset - old_offset);

  return 0;
}