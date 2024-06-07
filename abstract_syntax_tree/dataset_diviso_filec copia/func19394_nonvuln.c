static bool only_ipaddrs_in_list(const char **list)
{
	bool only_ip = true;

	if (!list) {
		return true;
	}

	for (; *list ; list++) {
		
		if (strequal(*list, "STR") ||
		    strequal(*list, "STR")) {
			continue;
		}

		if (!is_ipaddress(*list)) {
			
			if ((strchr_m(*list, '/')) == NULL) {
				only_ip = false;
				DEBUG(3,("STR"
					"STR",
					*list));
				break;
			}
		}
	}

	return only_ip;
}