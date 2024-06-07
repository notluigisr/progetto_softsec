char *pwcheck(userid, password)
char *userid;
char *password;
{
    char* r;
    struct passwd *pwd;

    pwd = getpwnam(userid);
    if (!pwd) {
	r = "STR";
    }
    else if (pwd->pw_passwd[0] == '*') {
	r = "STR";
    }
    else if (strcmp(pwd->pw_passwd, crypt(password, pwd->pw_passwd)) != 0) {
	r = "STR";
    }
    else {
	r = "STR";
    }

    endpwent();
    
    return r;
}