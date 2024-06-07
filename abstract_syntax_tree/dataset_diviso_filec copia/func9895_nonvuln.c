gst_rmdemux_reset (GstRMDemux * rmdemux)
{
  GSList *cur;

  GST_OBJECT_LOCK (rmdemux);
  rmdemux->running = FALSE;
  GST_OBJECT_UNLOCK (rmdemux);

  for (cur = rmdemux->streams; cur; cur = cur->next) {
    GstRMDemuxStream *stream = cur->data;

    gst_flow_combiner_remove_pad (rmdemux->flowcombiner, stream->pad);
    gst_element_remove_pad (GST_ELEMENT (rmdemux), stream->pad);
    gst_rmdemux_free_stream (rmdemux, stream);
  }
  g_slist_free (rmdemux->streams);
  rmdemux->streams = NULL;
  rmdemux->n_audio_streams = 0;
  rmdemux->n_video_streams = 0;

  if (rmdemux->pending_tags != NULL) {
    gst_tag_list_unref (rmdemux->pending_tags);
    rmdemux->pending_tags = NULL;
  }

  gst_adapter_clear (rmdemux->adapter);
  rmdemux->state = RMDEMUX_STATE_HEADER;
  rmdemux->have_pads = FALSE;

  gst_segment_init (&rmdemux->segment, GST_FORMAT_UNDEFINED);
  rmdemux->first_ts = GST_CLOCK_TIME_NONE;
  rmdemux->base_ts = GST_CLOCK_TIME_NONE;
  rmdemux->need_newsegment = TRUE;

  rmdemux->have_group_id = FALSE;
  rmdemux->group_id = G_MAXUINT;
}