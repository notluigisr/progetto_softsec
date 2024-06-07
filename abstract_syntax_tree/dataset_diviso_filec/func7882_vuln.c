PJ_DEF(void) pjmedia_rtcp_init2( pjmedia_rtcp_session *sess,
				 const pjmedia_rtcp_session_setting *settings)
{
    pjmedia_rtcp_sr_pkt *sr_pkt = &sess->rtcp_sr_pkt;
    pj_time_val now;
    
    
    pj_bzero(sess, sizeof(pjmedia_rtcp_session));

    
    sess->rtp_last_ts = (unsigned)-1;

    
    sess->name = settings->name ? settings->name : (char*)THIS_FILE;

    
    sess->clock_rate = settings->clock_rate;
    sess->pkt_size = settings->samples_per_frame;

    
    sr_pkt->common.version = 2;
    sr_pkt->common.count = 1;
    sr_pkt->common.pt = RTCP_SR;
    sr_pkt->common.length = pj_htons(12);
    sr_pkt->common.ssrc = pj_htonl(settings->ssrc);
    
    
    pj_memcpy(&sess->rtcp_rr_pkt.common, &sr_pkt->common, 
	      sizeof(pjmedia_rtcp_common));
    sess->rtcp_rr_pkt.common.pt = RTCP_RR;
    sess->rtcp_rr_pkt.common.length = pj_htons(7);

    
    pj_gettimeofday(&now);
    sess->tv_base = now;
    pj_get_timestamp(&sess->ts_base);
    pj_get_timestamp_freq(&sess->ts_freq);
    sess->rtp_ts_base = settings->rtp_ts_base;

    
    pjmedia_rtcp_init_stat(&sess->stat);

    
}