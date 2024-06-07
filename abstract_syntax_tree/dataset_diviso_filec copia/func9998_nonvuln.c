f_server2client(typval_T *argvars UNUSED, typval_T *rettv)
{
#ifdef FEAT_CLIENTSERVER
    char_u	buf[NUMBUFLEN];
    char_u	*server = tv_get_string_chk(&argvars[0]);
    char_u	*reply = tv_get_string_buf_chk(&argvars[1], buf);

    rettv->vval.v_number = -1;
    if (server == NULL || reply == NULL)
	return;
    if (check_restricted() || check_secure())
	return;
# ifdef FEAT_X11
    if (check_connection() == FAIL)
	return;
# endif

    if (serverSendReply(server, reply) < 0)
    {
	emsg(_("STR"));
	return;
    }
    rettv->vval.v_number = 0;
#else
    rettv->vval.v_number = -1;
#endif
}