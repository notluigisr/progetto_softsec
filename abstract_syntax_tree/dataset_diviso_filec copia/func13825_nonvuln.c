ews_soup_got_chunk (SoupMessage *msg,
                    SoupBuffer *chunk,
                    gpointer user_data)
{
	struct _oal_req_data *data = (struct _oal_req_data *) user_data;
	gint fd;

	if (msg->status_code != 200)
		return;

	data->received_size += chunk->length;

	if (data->response_size && data->progress_fn) {
		gint pc = data->received_size * 100 / data->response_size;
		data->progress_fn (data->progress_data, pc);
	}

	fd = g_open (data->cache_filename, O_RDONLY | O_WRONLY | O_APPEND | O_CREAT, 0600);
	if (fd != -1) {
		if (write (fd, (const gchar *) chunk->data, chunk->length) != chunk->length) {
			g_set_error (
				&data->error, EWS_CONNECTION_ERROR, EWS_CONNECTION_ERROR_UNKNOWN,
				"STR", data->cache_filename, g_strerror (errno));
		}
		close (fd);
	} else {
		g_set_error (
			&data->error, EWS_CONNECTION_ERROR, EWS_CONNECTION_ERROR_UNKNOWN,
			"STR", data->cache_filename, g_strerror (errno));
	}
}