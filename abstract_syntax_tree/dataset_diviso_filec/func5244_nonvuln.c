kuid_t make_kuid(struct user_namespace *ns, uid_t uid)
{
	
	return KUIDT_INIT(map_id_down(&ns->uid_map, uid));
}