void test_nghttp2_submit_window_update(void) {
  nghttp2_session *session;
  nghttp2_session_callbacks callbacks;
  my_user_data ud;
  nghttp2_outbound_item *item;
  nghttp2_stream *stream;

  memset(&callbacks, 0, sizeof(nghttp2_session_callbacks));
  callbacks.send_callback = null_send_callback;

  nghttp2_session_client_new(&session, &callbacks, &ud);
  stream = open_recv_stream(session, 2);
  stream->recv_window_size = 4096;

  CU_ASSERT(0 ==
            nghttp2_submit_window_update(session, NGHTTP2_FLAG_NONE, 2, 1024));
  item = nghttp2_session_get_next_ob_item(session);
  CU_ASSERT(NGHTTP2_WINDOW_UPDATE == item->frame.hd.type);
  CU_ASSERT(1024 == item->frame.window_update.window_size_increment);
  CU_ASSERT(0 == nghttp2_session_send(session));
  CU_ASSERT(3072 == stream->recv_window_size);

  CU_ASSERT(0 ==
            nghttp2_submit_window_update(session, NGHTTP2_FLAG_NONE, 2, 4096));
  item = nghttp2_session_get_next_ob_item(session);
  CU_ASSERT(NGHTTP2_WINDOW_UPDATE == item->frame.hd.type);
  CU_ASSERT(4096 == item->frame.window_update.window_size_increment);
  CU_ASSERT(0 == nghttp2_session_send(session));
  CU_ASSERT(0 == stream->recv_window_size);

  CU_ASSERT(0 ==
            nghttp2_submit_window_update(session, NGHTTP2_FLAG_NONE, 2, 4096));
  item = nghttp2_session_get_next_ob_item(session);
  CU_ASSERT(NGHTTP2_WINDOW_UPDATE == item->frame.hd.type);
  CU_ASSERT(4096 == item->frame.window_update.window_size_increment);
  CU_ASSERT(0 == nghttp2_session_send(session));
  CU_ASSERT(0 == stream->recv_window_size);

  CU_ASSERT(0 ==
            nghttp2_submit_window_update(session, NGHTTP2_FLAG_NONE, 2, 0));
  
  CU_ASSERT(0 ==
            nghttp2_submit_window_update(session, NGHTTP2_FLAG_NONE, 4, 4096));

  nghttp2_session_del(session);
}