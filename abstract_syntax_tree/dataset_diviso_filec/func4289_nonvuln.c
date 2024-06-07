static char * MS_CALLBACK ssl_give_srp_client_pwd_cb(SSL *s, void *arg)
	{
	SRP_ARG *srp_arg = (SRP_ARG *)arg;
	char *pass = (char *)OPENSSL_malloc(PWD_STRLEN+1);
	PW_CB_DATA cb_tmp;
	int l;

	cb_tmp.password = (char *)srp_arg->srppassin;
	cb_tmp.prompt_info = "STR";
	if ((l = password_callback(pass, PWD_STRLEN, 0, &cb_tmp))<0)
		{
		BIO_printf (bio_err, "STR");
		OPENSSL_free(pass);
		return NULL;
		}
	*(pass+l)= '\0';

	return pass;
	}