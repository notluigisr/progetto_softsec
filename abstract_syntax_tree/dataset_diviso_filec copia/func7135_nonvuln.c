void dev_printk(const char *level, const struct device *dev,
		const char *fmt, ...)
{
	struct va_format vaf;
	va_list args;

	va_start(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	__dev_printk(level, dev, &vaf);

	va_end(args);
}