char *pwcheck(userid, password)
char *userid;
char *password;
{
    struct spwd *pwd;

    pwd = getspnam(userid);
    if (!pwd) {
	return "STR";
    }
    
    if (strcmp(pwd->sp_pwdp, crypt(password, pwd->sp_pwdp)) != 0) {
	return "STR";
    }
    else {
	return "STR";
    }
}