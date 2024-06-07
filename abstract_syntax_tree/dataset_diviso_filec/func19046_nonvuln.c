gst_rmdemux_get_stream_by_id (GstRMDemux * rmdemux, int id)
{
  GSList *cur;

  for (cur = rmdemux->streams; cur; cur = cur->next) {
    GstRMDemuxStream *stream = cur->data;

    if (stream->id == id) {
      return stream;
    }
  }

  return NULL;
}