connection_handle_read_body_unknown (request_st * const r, chunkqueue * const cq, chunkqueue * const dst_cq)
{
    
    const off_t max_request_size = (off_t)r->conf.max_request_size << 10;
    chunkqueue_append_chunkqueue(dst_cq, cq);
    if (0 != max_request_size && dst_cq->bytes_in > max_request_size) {
        log_error(r->conf.errh, __FILE__, __LINE__,
          "STR", (long long)dst_cq->bytes_in);
        
        return http_response_reqbody_read_error(r, 413);
    }
    return HANDLER_GO_ON;
}