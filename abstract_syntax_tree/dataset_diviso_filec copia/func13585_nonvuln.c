static void get_mirc_color(const char **str, int *fg_ret, int *bg_ret)
{
	int fg, bg;

	fg = fg_ret == NULL ? -1 : *fg_ret;
	bg = bg_ret == NULL ? -1 : *bg_ret;

	if (!i_isdigit(**str) && **str != ',') {
		fg = -1;
		bg = -1;
	} else {
		
		if (**str != ',') {
			fg = **str-'0';
			(*str)++;
			if (i_isdigit(**str)) {
				fg = fg*10 + (**str-'0');
				(*str)++;
			}
		}
		if (**str == ',') {
			
			if (!i_isdigit((*str)[1]))
				bg = -1;
			else {
				(*str)++;
				bg = **str-'0';
				(*str)++;
				if (i_isdigit(**str)) {
					bg = bg*10 + (**str-'0');
					(*str)++;
				}
			}
		}
	}

	if (fg_ret) *fg_ret = fg;
	if (bg_ret) *bg_ret = bg;
}