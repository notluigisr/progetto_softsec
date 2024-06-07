TmEcode StreamTcpThreadInit(ThreadVars *tv, void *initdata, void **data)
{
    SCEnter();
    StreamTcpThread *stt = SCMalloc(sizeof(StreamTcpThread));
    if (unlikely(stt == NULL))
        SCReturnInt(TM_ECODE_FAILED);
    memset(stt, 0, sizeof(StreamTcpThread));
    stt->ssn_pool_id = -1;

    *data = (void *)stt;

    stt->counter_tcp_sessions = StatsRegisterCounter("STR", tv);
    stt->counter_tcp_ssn_memcap = StatsRegisterCounter("STR", tv);
    stt->counter_tcp_pseudo = StatsRegisterCounter("STR", tv);
    stt->counter_tcp_pseudo_failed = StatsRegisterCounter("STR", tv);
    stt->counter_tcp_invalid_checksum = StatsRegisterCounter("STR", tv);
    stt->counter_tcp_no_flow = StatsRegisterCounter("STR", tv);
    stt->counter_tcp_syn = StatsRegisterCounter("STR", tv);
    stt->counter_tcp_synack = StatsRegisterCounter("STR", tv);
    stt->counter_tcp_rst = StatsRegisterCounter("STR", tv);
    stt->counter_tcp_midstream_pickups = StatsRegisterCounter("STR", tv);
    stt->counter_tcp_wrong_thread = StatsRegisterCounter("STR", tv);

    
    stt->ra_ctx = StreamTcpReassembleInitThreadCtx(tv);
    if (stt->ra_ctx == NULL)
        SCReturnInt(TM_ECODE_FAILED);

    stt->ra_ctx->counter_tcp_segment_memcap = StatsRegisterCounter("STR", tv);
    stt->ra_ctx->counter_tcp_stream_depth = StatsRegisterCounter("STR", tv);
    stt->ra_ctx->counter_tcp_reass_gap = StatsRegisterCounter("STR", tv);
    stt->ra_ctx->counter_tcp_reass_overlap = StatsRegisterCounter("STR", tv);
    stt->ra_ctx->counter_tcp_reass_overlap_diff_data = StatsRegisterCounter("STR", tv);

    stt->ra_ctx->counter_tcp_reass_data_normal_fail = StatsRegisterCounter("STR", tv);
    stt->ra_ctx->counter_tcp_reass_data_overlap_fail = StatsRegisterCounter("STR", tv);
    stt->ra_ctx->counter_tcp_reass_list_fail = StatsRegisterCounter("STR", tv);


    SCLogDebug("STR",
                stt, stt->ra_ctx);

    SCMutexLock(&ssn_pool_mutex);
    if (ssn_pool == NULL) {
        ssn_pool = PoolThreadInit(1, 
                0, 
                stream_config.prealloc_sessions,
                sizeof(TcpSession),
                StreamTcpSessionPoolAlloc,
                StreamTcpSessionPoolInit, NULL,
                StreamTcpSessionPoolCleanup, NULL);
        stt->ssn_pool_id = 0;
        SCLogDebug("STR", PoolThreadSize(ssn_pool), stt->ssn_pool_id);
    } else {
        
        stt->ssn_pool_id = PoolThreadGrow(ssn_pool,
                0, 
                stream_config.prealloc_sessions,
                sizeof(TcpSession),
                StreamTcpSessionPoolAlloc,
                StreamTcpSessionPoolInit, NULL,
                StreamTcpSessionPoolCleanup, NULL);
        SCLogDebug("STR", PoolThreadSize(ssn_pool), stt->ssn_pool_id);
    }
    SCMutexUnlock(&ssn_pool_mutex);
    if (stt->ssn_pool_id < 0 || ssn_pool == NULL) {
        SCLogError(SC_ERR_MEM_ALLOC, "STR");
        SCReturnInt(TM_ECODE_FAILED);
    }

    SCReturnInt(TM_ECODE_OK);
}