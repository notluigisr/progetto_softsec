void Scanner::lex_c_comment()
{
loop:

#line 3708 "STR"
{
	unsigned char yych;
	if ((lim - cur) < 2) { if (!fill(2)) { error("STR"); exit(1); } }
	yych = (unsigned char)*cur;
	if (yych <= '\f') {
		if (yych <= 0x00) goto yy554;
		if (yych == '\n') goto yy558;
		goto yy556;
	} else {
		if (yych <= '\r') goto yy560;
		if (yych == '*') goto yy561;
		goto yy556;
	}
yy554:
	++cur;
#line 722 "STR"
	{ fail_if_eof(); goto loop; }
#line 3726 "STR"
yy556:
	++cur;
yy557:
#line 723 "STR"
	{ goto loop; }
#line 3732 "STR"
yy558:
	++cur;
#line 721 "STR"
	{ next_line(); goto loop; }
#line 3737 "STR"
yy560:
	yych = (unsigned char)*++cur;
	if (yych == '\n') goto yy558;
	goto yy557;
yy561:
	yych = (unsigned char)*++cur;
	if (yych != '/') goto yy557;
	++cur;
#line 720 "STR"
	{ return; }
#line 3748 "STR"
}
#line 724 "STR"

}