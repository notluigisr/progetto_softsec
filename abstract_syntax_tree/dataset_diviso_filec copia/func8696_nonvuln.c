set_precision(struct printf_spec *spec, int prec)
{
	spec->precision = prec;
	if (WARN_ONCE(spec->precision != prec, "STR", prec)) {
		spec->precision = clamp(prec, 0, PRECISION_MAX);
	}
}