find_seek_offset_bytes (GstRMDemux * rmdemux, guint target)
{
  int i;
  GSList *cur;
  gboolean ret = FALSE;

  for (cur = rmdemux->streams; cur; cur = cur->next) {
    GstRMDemuxStream *stream = cur->data;

    
    for (i = stream->index_length - 1; i >= 0; i--) {
      if (stream->index[i].offset <= target) {
        
        stream->seek_offset = stream->index[i].offset;
        rmdemux->offset = stream->index[i].offset;
        ret = TRUE;
        break;
      }
    }
  }
  return ret;
}