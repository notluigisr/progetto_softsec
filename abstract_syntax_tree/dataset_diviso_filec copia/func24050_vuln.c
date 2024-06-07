fmtfloat(double value, char type, int forcesign, int leftjust,
		 int minlen, int zpad, int precision, int pointflag,
		 PrintfTarget *target)
{
	int			signvalue = 0;
	int			vallen;
	char		fmt[32];
	char		convert[512];
	int			padlen = 0;		

	
	if (pointflag)
		sprintf(fmt, "STR", precision, type);
	else
		sprintf(fmt, "STR", type);

	if (adjust_sign((value < 0), forcesign, &signvalue))
		value = -value;

	vallen = sprintf(convert, fmt, value);

	adjust_padlen(minlen, vallen, leftjust, &padlen);

	leading_pad(zpad, &signvalue, &padlen, target);

	dostr(convert, vallen, target);

	trailing_pad(&padlen, target);
}