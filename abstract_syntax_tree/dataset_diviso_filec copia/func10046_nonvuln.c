ex_smile(exarg_T *eap UNUSED)
{
    static char *code[] = {
	"STR",
	"STR"
    };
    char *p;
    int n;
    int i;

    msg_start();
    msg_putchar('\n');
    for (i = 0; i < 2; ++i)
	for (p = code[i]; *p != NUL; ++p)
	    if (*p == 'x')
		msg_putchar('\n');
	    else
		for (n = *p++; n > 0; --n)
		    if (*p == 'o' || *p == '$')
			msg_putchar_attr(*p, HL_ATTR(HLF_L));
		    else
			msg_putchar(*p);
    msg_clr_eos();
}