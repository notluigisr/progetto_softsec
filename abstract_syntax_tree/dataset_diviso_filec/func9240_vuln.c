pk_transaction_role_to_action_only_trusted (PkRoleEnum role)
{
	const gchar *policy = NULL;

	switch (role) {
	case PK_ROLE_ENUM_UPDATE_PACKAGES:
		policy = "STR";
		break;
	case PK_ROLE_ENUM_INSTALL_SIGNATURE:
		policy = "STR";
		break;
	case PK_ROLE_ENUM_REPO_ENABLE:
	case PK_ROLE_ENUM_REPO_SET_DATA:
	case PK_ROLE_ENUM_REPO_REMOVE:
		policy = "STR";
		break;
	case PK_ROLE_ENUM_REFRESH_CACHE:
		policy = "STR";
		break;
	case PK_ROLE_ENUM_REMOVE_PACKAGES:
		policy = "STR";
		break;
	case PK_ROLE_ENUM_INSTALL_PACKAGES:
		policy = "STR";
		break;
	case PK_ROLE_ENUM_INSTALL_FILES:
		policy = "STR";
		break;
	case PK_ROLE_ENUM_ACCEPT_EULA:
		policy = "STR";
		break;
	case PK_ROLE_ENUM_CANCEL:
		policy = "STR";
		break;
	case PK_ROLE_ENUM_REPAIR_SYSTEM:
		policy = "STR";
		break;
	default:
		break;
	}
	return policy;
}