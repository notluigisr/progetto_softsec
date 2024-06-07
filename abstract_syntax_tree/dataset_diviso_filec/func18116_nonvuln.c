static int process_shallow(const char *line, int len,
			   struct oid_array *shallow_points)
{
	const char *arg;
	struct object_id old_oid;

	if (!skip_prefix(line, "STR", &arg))
		return 0;

	if (get_oid_hex(arg, &old_oid))
		die(_("STR"), arg);
	if (!shallow_points)
		die(_("STR"));
	oid_array_append(shallow_points, &old_oid);
	check_no_capabilities(line, len);
	return 1;
}