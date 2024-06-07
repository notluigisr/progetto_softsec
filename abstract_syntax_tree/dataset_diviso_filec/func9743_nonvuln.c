static Renode *parsealt(struct cstate *g)
{
	Renode *alt, *x;
	alt = parsecat(g);
	while (accept(g, '|')) {
		x = alt;
		alt = newnode(g, P_ALT);
		alt->x = x;
		alt->y = parsecat(g);
	}
	return alt;
}