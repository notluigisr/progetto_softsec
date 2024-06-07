const AST *Scanner::lex_cls(bool neg)
{
    std::vector<ASTRange> *cls = new std::vector<ASTRange>;
    uint32_t u, l;
    const loc_t &loc0 = tok_loc();
    loc_t loc = cur_loc();
fst:
    tok = cur;

#line 3805 "STR"
{
	unsigned char yych;
	if (lim <= cur) { if (!fill(1)) { error("STR"); exit(1); } }
	yych = (unsigned char)*cur;
	if (yych == ']') goto yy576;
#line 747 "STR"
	{ l = lex_cls_chr(); goto snd; }
#line 3813 "STR"
yy576:
	++cur;
#line 746 "STR"
	{ return ast_cls(loc0, cls, neg); }
#line 3818 "STR"
}
#line 748 "STR"

snd:

#line 3824 "STR"
{
	unsigned char yych;
	if ((lim - cur) < 2) { if (!fill(2)) { error("STR"); exit(1); } }
	yych = (unsigned char)*(mar = cur);
	if (yych == '-') goto yy581;
yy580:
#line 751 "STR"
	{ u = l; goto add; }
#line 3833 "STR"
yy581:
	yych = (unsigned char)*++cur;
	if (yych != ']') goto yy583;
	cur = mar;
	goto yy580;
yy583:
	++cur;
	cur -= 1;
#line 752 "STR"
	{
        u = lex_cls_chr();
        if (l > u) {
            msg.warn.swapped_range(loc, l, u);
            std::swap(l, u);
        }
        goto add;
    }
#line 3851 "STR"
}
#line 760 "STR"

add:
    cls->push_back(ASTRange(l, u, loc));
    loc = cur_loc();
    goto fst;
}