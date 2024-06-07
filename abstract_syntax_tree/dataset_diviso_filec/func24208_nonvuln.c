static void print_canon_ace(canon_ace *pace, int num)
{
	dbgtext( "STR" );
	dbgtext( "STR", sid_string_dbg(&pace->trustee));
	if (pace->owner_type == UID_ACE) {
		const char *u_name = uidtoname(pace->unix_ug.uid);
		dbgtext( "STR", (unsigned int)pace->unix_ug.uid, u_name );
	} else if (pace->owner_type == GID_ACE) {
		char *g_name = gidtoname(pace->unix_ug.gid);
		dbgtext( "STR", (unsigned int)pace->unix_ug.gid, g_name );
	} else
		dbgtext( "STR");
	switch (pace->type) {
		case SMB_ACL_USER:
			dbgtext( "STR");
			break;
		case SMB_ACL_USER_OBJ:
			dbgtext( "STR");
			break;
		case SMB_ACL_GROUP:
			dbgtext( "STR");
			break;
		case SMB_ACL_GROUP_OBJ:
			dbgtext( "STR");
			break;
		case SMB_ACL_OTHER:
			dbgtext( "STR");
			break;
		default:
			dbgtext( "STR" );
			break;
	}
	if (pace->inherited)
		dbgtext( "STR");
	dbgtext( "STR");
	dbgtext( "STR", pace->perms & S_IRUSR ? 'r' : '-');
	dbgtext( "STR", pace->perms & S_IWUSR ? 'w' : '-');
	dbgtext( "STR", pace->perms & S_IXUSR ? 'x' : '-');
}