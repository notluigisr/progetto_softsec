qedi_dbg_warn(struct qedi_dbg_ctx *qedi, const char *func, u32 line,
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

	if (!(qedi_dbg_log & QEDI_LOG_WARN))
		goto ret;

	if (likely(qedi) && likely(qedi->pdev))
		pr_warn("STR", dev_name(&qedi->pdev->dev),
			nfunc, line, qedi->host_no, &vaf);
	else
		pr_warn("STR", nfunc, line, &vaf);

ret:
	va_end(va);
}