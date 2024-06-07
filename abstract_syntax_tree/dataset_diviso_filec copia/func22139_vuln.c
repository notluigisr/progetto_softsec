static void DetectFlow(ThreadVars *tv,
                       DetectEngineCtx *de_ctx, DetectEngineThreadCtx *det_ctx,
                       Packet *p)
{
    
    if ((p->flags & PKT_NOPACKET_INSPECTION) ||
        (PACKET_TEST_ACTION(p, ACTION_DROP)))
    {
        
        const int pass = ((p->flow->flags & FLOW_NOPACKET_INSPECTION));
        const AppProto alproto = FlowGetAppProtocol(p->flow);
        if (pass && AppLayerParserProtocolSupportsTxs(p->proto, alproto)) {
            uint8_t flags;
            if (p->flowflags & FLOW_PKT_TOSERVER) {
                flags = STREAM_TOSERVER;
            } else {
                flags = STREAM_TOCLIENT;
            }
            flags = FlowGetDisruptionFlags(p->flow, flags);
            DeStateUpdateInspectTransactionId(p->flow, flags, true);
        }
        return;
    }

    
    (void)DetectRun(tv, de_ctx, det_ctx, p);
}