nfsd4_layout_verify(struct svc_export *exp, unsigned int layout_type)
{
	if (!exp->ex_layout_types) {
		dprintk("STR", __func__);
		return NULL;
	}

	if (!(exp->ex_layout_types & (1 << layout_type))) {
		dprintk("STR",
			__func__, layout_type);
		return NULL;
	}

	return nfsd4_layout_ops[layout_type];
}