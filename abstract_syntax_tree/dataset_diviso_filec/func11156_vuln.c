static bool new_idmap_permitted(struct user_namespace *ns, int cap_setid,
				struct uid_gid_map *new_map)
{
	
	if ((new_map->nr_extents == 1) && (new_map->extent[0].count == 1)) {
		u32 id = new_map->extent[0].lower_first;
		if (cap_setid == CAP_SETUID) {
			kuid_t uid = make_kuid(ns->parent, id);
			if (uid_eq(uid, current_fsuid()))
				return true;
		}
		else if (cap_setid == CAP_SETGID) {
			kgid_t gid = make_kgid(ns->parent, id);
			if (gid_eq(gid, current_fsgid()))
				return true;
		}
	}

	
	if (!cap_valid(cap_setid))
		return true;

	
	if (ns_capable(ns->parent, cap_setid))
		return true;

	return false;
}