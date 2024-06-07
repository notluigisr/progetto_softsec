static void do_list(sourceinfo_t *si, mychan_t *mc, unsigned int flags)
{
	chanacs_t *ca;
	mowgli_node_t *n;
	bool operoverride = false;
	unsigned int i = 1;

	if (!(mc->flags & MC_PUBACL) && !chanacs_source_has_flag(mc, si, CA_ACLVIEW))
	{
		if (has_priv(si, PRIV_CHAN_AUSPEX))
			operoverride = true;
		else
		{
			command_fail(si, fault_noprivs, _("STR"));
			return;
		}
	}

	command_success_nodata(si, _("STR"));
	command_success_nodata(si, "STR");

	MOWGLI_ITER_FOREACH(n, mc->chanacs.head)
	{
		const char *template, *mod_ago;
		struct tm tm;
		char mod_date[64];

		ca = n->data;

		if (flags && !(ca->level & flags))
			continue;

		template = get_template_name(mc, ca->level);
		mod_ago = ca->tmodified ? time_ago(ca->tmodified) : "STR";

		tm = *localtime(&ca->tmodified);
		strftime(mod_date, sizeof mod_date, TIME_FORMAT, &tm);

		if (template != NULL)
			command_success_nodata(si, _("STR"),
				i, ca->entity ? ca->entity->name : ca->host, bitmask_to_flags(ca->level), template, mc->name, mod_ago, mod_date);
		else
			command_success_nodata(si, _("STR"),
				i, ca->entity ? ca->entity->name : ca->host, bitmask_to_flags(ca->level), mc->name, mod_ago, mod_date);
		i++;
	}

	command_success_nodata(si, "STR");
	command_success_nodata(si, _("STR"), mc->name);

	if (operoverride)
		logcommand(si, CMDLOG_ADMIN, "STR", mc->name);
	else
		logcommand(si, CMDLOG_GET, "STR", mc->name);
}