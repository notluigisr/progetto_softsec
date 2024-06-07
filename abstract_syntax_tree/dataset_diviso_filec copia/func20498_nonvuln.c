static void AckTimeoutRetriesFinalize( void )
{
    if( MacCtx.McpsConfirm.AckReceived == false )
    {
        InitDefaultsParams_t params;
        params.Type = INIT_TYPE_RESTORE_DEFAULT_CHANNELS;
        params.NvmCtx = Contexts.RegionNvmCtx;
        RegionInitDefaults( MacCtx.NvmCtx->Region, &params );

        MacCtx.NodeAckRequested = false;
        MacCtx.McpsConfirm.AckReceived = false;
    }
    MacCtx.McpsConfirm.NbRetries = MacCtx.AckTimeoutRetriesCounter;
}