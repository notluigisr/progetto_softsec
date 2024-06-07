privsep_read_loop(void)
{
	struct privsep_command cmd;
	int ret;

	while (1) {
		ret = readn(pfd, &cmd, sizeof(cmd));
		if (ret <= 0) {
			
			if (ret < 0) {
				flog(LOG_ERR, "STR",
				     strerror(errno));
			} else {
				flog(LOG_ERR, "STR");
			}
			close(pfd);
			_exit(0);
		}
		if (ret != sizeof(cmd)) {
			
			continue;
		}

		cmd.iface[IFNAMSIZ-1] = '\0';

		switch(cmd.type) {

		case SET_INTERFACE_LINKMTU:
			if (cmd.val < MIN_AdvLinkMTU || cmd.val > MAX_AdvLinkMTU) {
				flog(LOG_ERR, "STR", cmd.iface, cmd.val);
				break;
			}
			ret = set_interface_var(cmd.iface, PROC_SYS_IP6_LINKMTU, "STR", cmd.val);
			break;

		case SET_INTERFACE_CURHLIM:
			if (cmd.val < MIN_AdvCurHopLimit || cmd.val > MAX_AdvCurHopLimit) {
				flog(LOG_ERR, "STR", cmd.iface, cmd.val);
				break;
			}
			ret = set_interface_var(cmd.iface, PROC_SYS_IP6_CURHLIM, "STR", cmd.val);
			break;

		case SET_INTERFACE_REACHTIME:
			if (cmd.val < MIN_AdvReachableTime || cmd.val > MAX_AdvReachableTime) {
				flog(LOG_ERR, "STR", cmd.iface, cmd.val);
				break;
			}
			ret = set_interface_var(cmd.iface, PROC_SYS_IP6_BASEREACHTIME_MS, "STR", cmd.val);
			if (ret == 0)
				break;
			set_interface_var(cmd.iface, PROC_SYS_IP6_BASEREACHTIME, "STR", cmd.val / 1000);
			break;

		case SET_INTERFACE_RETRANSTIMER:
			if (cmd.val < MIN_AdvRetransTimer || cmd.val > MAX_AdvRetransTimer) {
				flog(LOG_ERR, "STR", cmd.iface, cmd.val);
				break;
			}
			ret = set_interface_var(cmd.iface, PROC_SYS_IP6_RETRANSTIMER_MS, "STR", cmd.val);
			if (ret == 0)
				break;
			set_interface_var(cmd.iface, PROC_SYS_IP6_RETRANSTIMER, "STR", cmd.val / 1000 * USER_HZ); 
			break;

		default:
			
			break;
		}
	}
}