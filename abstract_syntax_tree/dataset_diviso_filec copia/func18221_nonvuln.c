static int AppLayerProtoDetectTest06(void)
{
    AppLayerProtoDetectUnittestCtxBackup();
    AppLayerProtoDetectSetup();

    uint8_t l7data[] = "STR";
    const char *buf;
    int r = 0;
    Flow f;
    AppProto pm_results[ALPROTO_MAX];
    AppLayerProtoDetectThreadCtx *alpd_tctx;

    memset(&f, 0x00, sizeof(f));
    f.protomap = FlowGetProtoMapping(IPPROTO_TCP);

    buf = "STR";
    AppLayerProtoDetectPMRegisterPatternCS(IPPROTO_TCP, ALPROTO_HTTP, buf, 4, 0, STREAM_TOCLIENT);
    buf = "STR";
    AppLayerProtoDetectPMRegisterPatternCS(IPPROTO_TCP, ALPROTO_FTP, buf, 4, 0, STREAM_TOCLIENT);

    AppLayerProtoDetectPrepareState();
    
    alpd_tctx = AppLayerProtoDetectGetCtxThread();

    if (alpd_ctx.ctx_ipp[FLOW_PROTO_TCP].ctx_pm[0].max_pat_id != 0) {
        printf("STR");
        goto end;
    }
    if (alpd_ctx.ctx_ipp[FLOW_PROTO_TCP].ctx_pm[1].max_pat_id != 2) {
        printf("STR");
        goto end;
    }

    if (alpd_ctx.ctx_ipp[FLOW_PROTO_TCP].ctx_pm[0].map != NULL) {
        printf("STR");
        goto end;
    }
    if (alpd_ctx.ctx_ipp[FLOW_PROTO_TCP].ctx_pm[1].map == NULL) {
        printf("STR");
        goto end;
    }

    if (alpd_ctx.ctx_ipp[FLOW_PROTO_TCP].ctx_pm[1].map[0]->alproto != ALPROTO_FTP) {
        printf("STR");
        goto end;
    }
    if (alpd_ctx.ctx_ipp[FLOW_PROTO_TCP].ctx_pm[1].map[1]->alproto != ALPROTO_HTTP) {
        printf("STR");
        goto end;
    }

    uint32_t cnt = AppLayerProtoDetectPMGetProto(alpd_tctx,
                                                 &f,
                                                 l7data, sizeof(l7data),
                                                 STREAM_TOCLIENT,
                                                 IPPROTO_TCP,
                                                 pm_results);
    if (cnt != 1 && pm_results[0] != ALPROTO_FTP) {
        printf("STR");
        goto end;
    }

    r = 1;

 end:
    if (alpd_tctx != NULL)
        AppLayerProtoDetectDestroyCtxThread(alpd_tctx);
    AppLayerProtoDetectDeSetup();
    AppLayerProtoDetectUnittestCtxRestore();
    return r;
}