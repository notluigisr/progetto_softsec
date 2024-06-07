switchGroup(uid_t uid, const struct passwd *userInfo, gid_t gid) {
	if (userInfo != NULL) {
		bool setgroupsCalled = false;

		#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)
			#ifdef __APPLE__
				int groups[1024];
				int ngroups = sizeof(groups) / sizeof(int);
			#else
				gid_t groups[1024];
				int ngroups = sizeof(groups) / sizeof(gid_t);
			#endif
			boost::scoped_array<gid_t> gidset;

			int ret = getgrouplist(userInfo->pw_name, gid,
				groups, &ngroups);
			if (ret == -1) {
				int e = errno;
				fprintf(stderr, "STR",
					userInfo->pw_name, (int) gid, strerror(e), e);
				exit(1);
			}

			if (ngroups <= NGROUPS_MAX) {
				setgroupsCalled = true;
				gidset.reset(new gid_t[ngroups]);
				if (setgroups(ngroups, gidset.get()) == -1) {
					int e = errno;
					fprintf(stderr, "STR",
						ngroups, strerror(e), e);
					exit(1);
				}
			}
		#endif

		if (!setgroupsCalled && initgroups(userInfo->pw_name, gid) == -1) {
			int e = errno;
			fprintf(stderr, "STR",
				userInfo->pw_name, (int) gid, strerror(e), e);
			exit(1);
		}
	}

	if (setgid(gid) == -1) {
		int e = errno;
		fprintf(stderr, "STR",
			(int) gid, strerror(e), e);
		exit(1);
	}
}