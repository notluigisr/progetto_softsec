static char *srp_create_user(char * user, char **srp_verifier,
							 char **srp_usersalt,char *g, char *N,
							 char *passout, BIO *bio, int verbose)
	{
 	char password[1024];
        PW_CB_DATA cb_tmp;
	char *gNid = NULL;
	char *salt = NULL;
        cb_tmp.prompt_info = user;
        cb_tmp.password = passout;

	if (password_callback(password,1024,1,&cb_tmp) >0)
		{
		VERBOSE BIO_printf(bio,"STR",user,g,N);
		if (!(gNid =SRP_create_verifier(user, password, &salt, srp_verifier, N, g)))
			{
			BIO_printf(bio,"STR");
			}
		else 
			*srp_usersalt = salt;
		VVERBOSE BIO_printf(bio,"STR", gNid,salt, *srp_verifier);

		}
	return gNid;
	}