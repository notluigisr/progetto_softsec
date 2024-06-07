ar6000_init_control_info(struct ar6_softc *ar)
{
    ar->arWmiEnabled         = false;
    ar6000_init_profile_info(ar);
    ar->arDefTxKeyIndex      = 0;
    A_MEMZERO(ar->arWepKeyList, sizeof(ar->arWepKeyList));
    ar->arChannelHint        = 0;
    ar->arListenIntervalT    = A_DEFAULT_LISTEN_INTERVAL;
    ar->arListenIntervalB    = 0;
    ar->arVersion.host_ver   = AR6K_SW_VERSION;
    ar->arRssi               = 0;
    ar->arTxPwr              = 0;
    ar->arTxPwrSet           = false;
    ar->arSkipScan           = 0;
    ar->arBeaconInterval     = 0;
    ar->arBitRate            = 0;
    ar->arMaxRetries         = 0;
    ar->arWmmEnabled         = true;
    ar->intra_bss            = 1;
    ar->scan_triggered       = 0;
    A_MEMZERO(&ar->scParams, sizeof(ar->scParams));
    ar->scParams.shortScanRatio = WMI_SHORTSCANRATIO_DEFAULT;
    ar->scParams.scanCtrlFlags = DEFAULT_SCAN_CTRL_FLAGS;

    
    {
        u8 ctr;
        A_MEMZERO((u8 *)ar->sta_list, AP_MAX_NUM_STA * sizeof(sta_t));

        
        A_MUTEX_INIT(&ar->mcastpsqLock);

        
        for (ctr=0; ctr < AP_MAX_NUM_STA ; ctr++) {
            A_MUTEX_INIT(&ar->sta_list[ctr].psqLock);
            A_NETBUF_QUEUE_INIT(&ar->sta_list[ctr].psq);
        }

        ar->ap_profile_flag = 0;
        A_NETBUF_QUEUE_INIT(&ar->mcastpsq);

        memcpy(ar->ap_country_code, DEF_AP_COUNTRY_CODE, 3);
        ar->ap_wmode = DEF_AP_WMODE_G;
        ar->ap_dtim_period = DEF_AP_DTIM;
        ar->ap_beacon_interval = DEF_BEACON_INTERVAL;
    }
}