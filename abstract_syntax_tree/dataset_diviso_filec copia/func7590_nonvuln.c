int X509_PURPOSE_add(int id, int trust, int flags,
			int (*ck)(const X509_PURPOSE *, const X509 *, int),
					char *name, char *sname, void *arg)
{
	int idx;
	X509_PURPOSE *ptmp;
	
	flags &= ~X509_PURPOSE_DYNAMIC;
	
	flags |= X509_PURPOSE_DYNAMIC_NAME;
	
	idx = X509_PURPOSE_get_by_id(id);
	
	if(idx == -1) {
		if(!(ptmp = OPENSSL_malloc(sizeof(X509_PURPOSE)))) {
			X509V3err(X509V3_F_X509_PURPOSE_ADD,ERR_R_MALLOC_FAILURE);
			return 0;
		}
		ptmp->flags = X509_PURPOSE_DYNAMIC;
	} else ptmp = X509_PURPOSE_get0(idx);

	
	if(ptmp->flags & X509_PURPOSE_DYNAMIC_NAME) {
		OPENSSL_free(ptmp->name);
		OPENSSL_free(ptmp->sname);
	}
	
	ptmp->name = BUF_strdup(name);
	ptmp->sname = BUF_strdup(sname);
	if(!ptmp->name || !ptmp->sname) {
		X509V3err(X509V3_F_X509_PURPOSE_ADD,ERR_R_MALLOC_FAILURE);
		return 0;
	}
	
	ptmp->flags &= X509_PURPOSE_DYNAMIC;
	
	ptmp->flags |= flags;

	ptmp->purpose = id;
	ptmp->trust = trust;
	ptmp->check_purpose = ck;
	ptmp->usr_data = arg;

	
	if(idx == -1) {
		if(!xptable && !(xptable = sk_X509_PURPOSE_new(xp_cmp))) {
			X509V3err(X509V3_F_X509_PURPOSE_ADD,ERR_R_MALLOC_FAILURE);
			return 0;
		}
		if (!sk_X509_PURPOSE_push(xptable, ptmp)) {
			X509V3err(X509V3_F_X509_PURPOSE_ADD,ERR_R_MALLOC_FAILURE);
			return 0;
		}
	}
	return 1;
}