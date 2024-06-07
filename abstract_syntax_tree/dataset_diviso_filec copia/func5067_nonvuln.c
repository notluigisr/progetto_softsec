static void attr_show_all_iterator(struct hash_backet *backet, struct vty *vty)
{
	struct attr *attr = backet->data;

	vty_out(vty, "STR", attr->refcnt,
		inet_ntoa(attr->nexthop));
	vty_out(vty, "STR",
		attr->flag, attr->med, attr->local_pref, attr->origin,
		attr->weight, attr->label);
}