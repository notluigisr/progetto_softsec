PJ_DEF(pj_status_t) pjmedia_rtp_session_init( pjmedia_rtp_session *ses,
					      int default_pt, 
					      pj_uint32_t sender_ssrc )
{
    PJ_LOG(5, (THIS_FILE, 
	       "STR",
	       ses, default_pt, sender_ssrc));

    
    if (sizeof(struct pjmedia_rtp_hdr) != 12) {
	pj_assert(!"STR");
	return PJMEDIA_RTP_EINPACK;
    }

    
    if (sender_ssrc == 0 || sender_ssrc == (pj_uint32_t)-1) {
	sender_ssrc = pj_htonl(pj_rand());
    } else {
	sender_ssrc = pj_htonl(sender_ssrc);
    }

    
    pj_bzero(ses, sizeof(*ses));

    
    
    ses->out_extseq = pj_rand() & 0x7FFF;
    ses->peer_ssrc = 0;
    
    
    ses->out_hdr.v = RTP_VERSION;
    ses->out_hdr.p = 0;
    ses->out_hdr.x = 0;
    ses->out_hdr.cc = 0;
    ses->out_hdr.m = 0;
    ses->out_hdr.pt = (pj_uint8_t) default_pt;
    ses->out_hdr.seq = (pj_uint16_t) pj_htons( (pj_uint16_t)ses->out_extseq );
    ses->out_hdr.ts = 0;
    ses->out_hdr.ssrc = sender_ssrc;

    
    ses->out_pt = (pj_uint16_t) default_pt;

    return PJ_SUCCESS;
}