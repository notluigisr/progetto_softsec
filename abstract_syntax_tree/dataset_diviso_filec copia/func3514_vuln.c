save_number(const char *fmt, int number, int len)
{
    if (len < 30)
	len = 30;		

    get_space((size_t) len + 1);

    _nc_SPRINTF(TPS(out_buff) + TPS(out_used),
		_nc_SLIMIT(TPS(out_size) - TPS(out_used))
		fmt, number);
    TPS(out_used) += strlen(TPS(out_buff) + TPS(out_used));
}