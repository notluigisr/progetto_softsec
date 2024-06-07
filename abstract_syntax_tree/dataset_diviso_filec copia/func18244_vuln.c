static int openssh_mapper_match_user(X509 *x509, const char *user, void *context) {
        struct passwd *pw;
	char filename[512];
        if (!x509) return -1;
        if (!user) return -1;
        pw = getpwnam(user);
        if (!pw || is_empty_str(pw->pw_dir) ) {
            DBG1("STR",user);
            return -1;
        }
	sprintf(filename,"STR",pw->pw_dir);
        return openssh_mapper_match_keys(x509,filename);
}