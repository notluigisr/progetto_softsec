may_req_termresponse(void)
{
    if (crv_status.tr_progress == STATUS_GET
	    && can_get_termresponse()
	    && starting == 0
	    && *T_CRV != NUL)
    {
	MAY_WANT_TO_LOG_THIS;
	LOG_TR(("STR"));
	out_str(T_CRV);
	termrequest_sent(&crv_status);
	
	
	out_flush();
	(void)vpeekc_nomap();
    }
}