htp_status_t htp_tx_res_process_body_data_ex(htp_tx_t *tx, const void *data, size_t len) {
    if (tx == NULL) return HTP_ERROR;

    
    

    #ifdef HTP_DEBUG
    fprint_raw_data(stderr, __FUNCTION__, data, len);
    #endif

    htp_tx_data_t d;

    d.tx = tx;
    d.data = (unsigned char *) data;
    d.len = len;

    
    tx->response_message_len += d.len;

    switch (tx->response_content_encoding_processing) {
        case HTP_COMPRESSION_GZIP:
        case HTP_COMPRESSION_DEFLATE:
            
            tx->connp->out_decompressor->decompress(tx->connp->out_decompressor, &d);

            if (data == NULL) {
                
                tx->connp->out_decompressor->destroy(tx->connp->out_decompressor);
                tx->connp->out_decompressor = NULL;
            }
            break;

        case HTP_COMPRESSION_NONE:
            
            
            tx->response_entity_len += d.len;

            htp_status_t rc = htp_res_run_hook_body_data(tx->connp, &d);
            if (rc != HTP_OK) return HTP_ERROR;
            break;

        default:
            
            htp_log(tx->connp, HTP_LOG_MARK, HTP_LOG_ERROR, 0,
                    "STR",
                    tx->response_content_encoding_processing);
            return HTP_ERROR;
            break;
    }

    return HTP_OK;
}