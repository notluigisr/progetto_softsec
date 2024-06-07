R_API char *r_bin_java_get_version(RBinJavaObj *bin) {
	return r_str_newf ("STR",
		bin->cf.major[1], bin->cf.major[0],
		bin->cf.minor[1], bin->cf.minor[0]);
}