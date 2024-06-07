static RBinInfo *info(RBinFile *arch) {
	RBinInfo *ret = R_NEW0 (RBinInfo);
	if (!ret) {
		return NULL;
	}
	ret->file = strdup (arch->file);
	ret->type = r_str_newf ("STR", version.version);
	ret->bclass = strdup ("STR");
	ret->rclass = strdup ("STR");
	ret->arch = strdup ("STR");
	ret->machine = r_str_newf ("STR", version.version,
		version.revision);
	ret->os = strdup ("STR");
	ret->bits = version2double (version.version) < 3.6? 16: 8;
	ret->cpu = strdup (version.version); 
	return ret;
}