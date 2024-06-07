static int h2_task_pre_conn(conn_rec* c, void *arg)
{
    h2_ctx *ctx;
    
    if (!c->master) {
        return OK;
    }
    
    ctx = h2_ctx_get(c, 0);
    (void)arg;
    if (ctx->task) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                      "STR");
        ap_add_input_filter("STR", NULL, NULL, c);
        ap_add_output_filter("STR", NULL, NULL, c);
        ap_add_output_filter("STR", NULL, NULL, c);
    }
    return OK;
}