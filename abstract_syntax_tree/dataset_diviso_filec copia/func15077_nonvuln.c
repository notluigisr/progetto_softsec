static int AppLayerProtoDetectTest12(void)
{
    AppLayerProtoDetectUnittestCtxBackup();
    AppLayerProtoDetectSetup();

    int r = 0;

    AppLayerProtoDetectPMRegisterPatternCS(IPPROTO_TCP, ALPROTO_HTTP, "STR", 4, 0, STREAM_TOSERVER);
    if (alpd_ctx.ctx_ipp[FLOW_PROTO_TCP].ctx_pm[0].head == NULL ||
        alpd_ctx.ctx_ipp[FLOW_PROTO_TCP].ctx_pm[0].map != NULL)
    {
        printf("STR");
        goto end;
    }

    AppLayerProtoDetectPrepareState();
    if (alpd_ctx.ctx_ipp[FLOW_PROTO_TCP].ctx_pm[0].max_pat_id != 1) {
        printf("STR");
        goto end;
    }
    if (alpd_ctx.ctx_ipp[FLOW_PROTO_TCP].ctx_pm[0].head != NULL ||
        alpd_ctx.ctx_ipp[FLOW_PROTO_TCP].ctx_pm[0].map == NULL)
    {
        printf("STR");
        goto end;
    }
    if (alpd_ctx.ctx_ipp[FLOW_PROTO_TCP].ctx_pm[0].map[0]->alproto != ALPROTO_HTTP) {
        printf("STR");
        goto end;
    }
    if (alpd_ctx.ctx_ipp[FLOW_PROTO_TCP].ctx_pm[0].map[0]->cd->id != 0) {
        printf("STR");
        goto end;
    }
    if (alpd_ctx.ctx_ipp[FLOW_PROTO_TCP].ctx_pm[0].map[0]->next != NULL) {
        printf("STR");
        goto end;
    }

    r = 1;

 end:
    AppLayerProtoDetectDeSetup();
    AppLayerProtoDetectUnittestCtxRestore();
    return r;
}