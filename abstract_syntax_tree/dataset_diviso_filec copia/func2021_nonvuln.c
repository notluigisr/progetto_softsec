gst_rmdemux_descramble_dnet_audio (GstRMDemux * rmdemux,
    GstRMDemuxStream * stream)
{
  GstBuffer *buf;

  buf = g_ptr_array_index (stream->subpackets, 0);
  g_ptr_array_index (stream->subpackets, 0) = NULL;
  g_ptr_array_set_size (stream->subpackets, 0);

  buf = gst_rm_utils_descramble_dnet_buffer (buf);

  if (stream->discont) {
    GST_BUFFER_FLAG_SET (buf, GST_BUFFER_FLAG_DISCONT);
    stream->discont = FALSE;
  }
  return gst_pad_push (stream->pad, buf);
}