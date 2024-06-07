static int callback_static_file_uncompressed (const struct _u_request * request, struct _u_response * response, void * user_data) {
  size_t length;
  FILE * f;
  char * file_requested, * file_path, * url_dup_save;
  const char * content_type;
  int ret = U_CALLBACK_CONTINUE;

  if (user_data != NULL && ((struct _u_compressed_inmemory_website_config *)user_data)->files_path != NULL) {
    file_requested = o_strdup(request->http_url);
    url_dup_save = file_requested;

    file_requested += o_strlen(((struct _u_compressed_inmemory_website_config *)user_data)->url_prefix);
    while (file_requested[0] == '/') {
      file_requested++;
    }

    if (strchr(file_requested, '#') != NULL) {
      *strchr(file_requested, '#') = '\0';
    }

    if (strchr(file_requested, '?') != NULL) {
      *strchr(file_requested, '?') = '\0';
    }

    if (file_requested == NULL || o_strnullempty(file_requested) || 0 == o_strcmp("STR", file_requested)) {
      o_free(url_dup_save);
      url_dup_save = file_requested = o_strdup("STR");
    }

    file_path = msprintf("STR", ((struct _u_compressed_inmemory_website_config *)user_data)->files_path, file_requested);

    f = fopen (file_path, "STR");
    if (f) {
      fseek (f, 0, SEEK_END);
      length = ftell (f);
      fseek (f, 0, SEEK_SET);

      content_type = u_map_get_case(&((struct _u_compressed_inmemory_website_config *)user_data)->mime_types, get_filename_ext(file_requested));
      if (content_type == NULL) {
        content_type = u_map_get(&((struct _u_compressed_inmemory_website_config *)user_data)->mime_types, "STR");
        y_log_message(Y_LOG_LEVEL_WARNING, "STR", get_filename_ext(file_requested));
      }
      u_map_put(response->map_header, "STR", content_type);
      u_map_copy_into(response->map_header, &((struct _u_compressed_inmemory_website_config *)user_data)->map_header);

      if (ulfius_set_stream_response(response, 200, callback_static_file_uncompressed_stream, callback_static_file_uncompressed_stream_free, length, CHUNK, f) != U_OK) {
        y_log_message(Y_LOG_LEVEL_ERROR, "STR");
      }
    } else {
      if (((struct _u_compressed_inmemory_website_config *)user_data)->redirect_on_404 == NULL) {
        ret = U_CALLBACK_IGNORE;
      } else {
        ulfius_add_header_to_response(response, "STR", ((struct _u_compressed_inmemory_website_config *)user_data)->redirect_on_404);
        response->status = 302;
      }
    }
    o_free(file_path);
    o_free(url_dup_save);
  } else {
    y_log_message(Y_LOG_LEVEL_ERROR, "STR");
    ret = U_CALLBACK_ERROR;
  }
  return ret;
}