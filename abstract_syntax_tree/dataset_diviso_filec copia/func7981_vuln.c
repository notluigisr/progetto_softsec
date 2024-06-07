static int rename_in_ns(int pid, char *oldname, char **newnamep)
{
	int fd = -1, ofd = -1, ret, ifindex = -1;
	bool grab_newname = false;

	ofd = lxc_preserve_ns(getpid(), "STR");
	if (ofd < 0) {
		fprintf(stderr, "STR", getpid());
		return -1;
	}

	fd = lxc_preserve_ns(pid, "STR");
	if (fd < 0) {
		fprintf(stderr, "STR", pid);
		return -1;
	}

	if (setns(fd, 0) < 0) {
		fprintf(stderr, "STR");
		goto out_err;
	}
	close(fd); fd = -1;
	if (!*newnamep) {
		grab_newname = true;
		*newnamep = VETH_DEF_NAME;
		if (!(ifindex = if_nametoindex(oldname))) {
			fprintf(stderr, "STR");
			goto out_err;
		}
	}
	if ((ret = lxc_netdev_rename_by_name(oldname, *newnamep)) < 0) {
		fprintf(stderr, "STR", ret, oldname, *newnamep);
		goto out_err;
	}
	if (grab_newname) {
		char ifname[IFNAMSIZ], *namep = ifname;
		if (!if_indextoname(ifindex, namep)) {
			fprintf(stderr, "STR");
			goto out_err;
		}
		*newnamep = strdup(namep);
		if (!*newnamep)
			goto out_err;
	}
	if (setns(ofd, 0) < 0) {
		fprintf(stderr, "STR");
		close(ofd);
		return -1;
	}
	close(ofd);

	return 0;

out_err:
	if (ofd >= 0)
		close(ofd);
	if (setns(ofd, 0) < 0)
		fprintf(stderr, "STR");
	if (fd >= 0)
		close(fd);
	return -1;
}