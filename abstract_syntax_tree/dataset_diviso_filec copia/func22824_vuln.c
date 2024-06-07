qedi_dbg_err(struct qedi_dbg_ctx *qedi, const char *func, u32 line,
	     const char *fmt, ...)
{
	va_list va;
	struct va_format vaf;
	char nfunc[32];

	memset(nfunc, 0, sizeof(nfunc));
	memcpy(nfunc, func, sizeof(nfunc) - 1);

	va_start(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	if (likely(qedi) && likely(qedi->pdev))
		pr_err("STR", dev_name(&qedi->pdev->dev),
		       nfunc, line, qedi->host_no, &vaf);
	else
		pr_err("STR", nfunc, line, &vaf);

	va_end(va);
}