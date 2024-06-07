int ConnectionImpl::onMetadataFrameComplete(int32_t stream_id, bool end_metadata) {
  ENVOY_CONN_LOG(trace, "STR", connection_,
                 stream_id, end_metadata);

  StreamImpl* stream = getStream(stream_id);
  if (stream == nullptr) {
    return 0;
  }

  bool result = stream->getMetadataDecoder().onMetadataFrameComplete(end_metadata);
  return result ? 0 : NGHTTP2_ERR_CALLBACK_FAILURE;
}