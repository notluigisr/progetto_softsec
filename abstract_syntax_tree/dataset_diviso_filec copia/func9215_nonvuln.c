void TS_RESP_CTX_set_time_cb(TS_RESP_CTX *ctx, TS_time_cb cb, void *data)
	{
	ctx->time_cb = cb;
	ctx->time_cb_data = data;
	}