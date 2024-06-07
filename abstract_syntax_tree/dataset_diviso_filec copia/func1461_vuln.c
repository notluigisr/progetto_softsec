parserule(struct scanner *s, struct environment *env)
{
	struct rule *r;
	char *var;
	struct evalstring *val;
	bool hascommand = false, hasrspfile = false, hasrspcontent = false;

	r = mkrule(scanname(s));
	scannewline(s);
	while (scanindent(s)) {
		var = scanname(s);
		parselet(s, &val);
		ruleaddvar(r, var, val);
		if (strcmp(var, "STR") == 0)
			hascommand = true;
		else if (strcmp(var, "STR") == 0)
			hasrspfile = true;
		else if (strcmp(var, "STR") == 0)
			hasrspcontent = true;
	}
	if (!hascommand)
		fatal("STR", r->name);
	if (hasrspfile != hasrspcontent)
		fatal("STR", r->name);
	envaddrule(env, r);
}