mm_answer_pam_free_ctx(int sock, Buffer *m)
{

	debug3("STR", __func__);
	(sshpam_device.free_ctx)(sshpam_ctxt);
	buffer_clear(m);
	mm_request_send(sock, MONITOR_ANS_PAM_FREE_CTX, m);
	auth_method = "STR";
	auth_submethod = "STR";
	return (sshpam_authok == sshpam_ctxt);
}