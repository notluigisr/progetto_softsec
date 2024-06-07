static int h2_task_process_conn(conn_rec* c)
{
    h2_ctx *ctx;
    
    if (!c->master) {
        return DECLINED;
    }
    
    ctx = h2_ctx_get(c, 0);
    if (ctx->task) {
        if (!ctx->task->request->serialize) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, 
                          "STR");
            h2_task_process_request(ctx->task, c);
            return DONE;
        }
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, 
                      "STR", ctx->task->id);
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, 
                      "STR", c->id);
    }
    return DECLINED;
}