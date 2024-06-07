static int audit_netlink_ok(struct sk_buff *skb, u16 msg_type)
{
	int err = 0;

	
	
	if (current_user_ns() != &init_user_ns)
		return -ECONNREFUSED;

	switch (msg_type) {
	case AUDIT_LIST:
	case AUDIT_ADD:
	case AUDIT_DEL:
		return -EOPNOTSUPP;
	case AUDIT_GET:
	case AUDIT_SET:
	case AUDIT_GET_FEATURE:
	case AUDIT_SET_FEATURE:
	case AUDIT_LIST_RULES:
	case AUDIT_ADD_RULE:
	case AUDIT_DEL_RULE:
	case AUDIT_SIGNAL_INFO:
	case AUDIT_TTY_GET:
	case AUDIT_TTY_SET:
	case AUDIT_TRIM:
	case AUDIT_MAKE_EQUIV:
		
		if ((task_active_pid_ns(current) != &init_pid_ns))
			return -EPERM;

		if (!capable(CAP_AUDIT_CONTROL))
			err = -EPERM;
		break;
	case AUDIT_USER:
	case AUDIT_FIRST_USER_MSG ... AUDIT_LAST_USER_MSG:
	case AUDIT_FIRST_USER_MSG2 ... AUDIT_LAST_USER_MSG2:
		if (!capable(CAP_AUDIT_WRITE))
			err = -EPERM;
		break;
	default:  
		err = -EINVAL;
	}

	return err;
}