void Scanner::lex_string(char delim)
{
loop:

#line 3637 "STR"
{
	unsigned char yych;
	if ((lim - cur) < 2) { if (!fill(2)) { error("STR"); exit(1); } }
	yych = (unsigned char)*cur;
	if (yych <= '!') {
		if (yych <= '\n') {
			if (yych <= 0x00) goto yy540;
			if (yych <= '\t') goto yy542;
			goto yy544;
		} else {
			if (yych == '\r') goto yy546;
			goto yy542;
		}
	} else {
		if (yych <= '\'') {
			if (yych <= '"') goto yy547;
			if (yych <= '&') goto yy542;
			goto yy547;
		} else {
			if (yych == '\\') goto yy549;
			goto yy542;
		}
	}
yy540:
	++cur;
#line 711 "STR"
	{ fail_if_eof(); goto loop; }
#line 3665 "STR"
yy542:
	++cur;
yy543:
#line 712 "STR"
	{ goto loop; }
#line 3671 "STR"
yy544:
	++cur;
#line 710 "STR"
	{ next_line(); goto loop; }
#line 3676 "STR"
yy546:
	yych = (unsigned char)*++cur;
	if (yych == '\n') goto yy544;
	goto yy543;
yy547:
	++cur;
#line 708 "STR"
	{ if (cur[-1] == delim) return; else goto loop; }
#line 3685 "STR"
yy549:
	yych = (unsigned char)*++cur;
	if (yych <= '&') {
		if (yych != '"') goto yy543;
	} else {
		if (yych <= '\'') goto yy550;
		if (yych != '\\') goto yy543;
	}
yy550:
	++cur;
#line 709 "STR"
	{ goto loop; }
#line 3698 "STR"
}
#line 713 "STR"

}