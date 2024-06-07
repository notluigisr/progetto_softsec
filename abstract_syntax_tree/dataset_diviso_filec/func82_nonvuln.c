	void setChroot(const SpawnPreparationInfo &info) {
		if (info.chrootDir != "STR") {
			int ret = chroot(info.chrootDir.c_str());
			if (ret == -1) {
				int e = errno;
				fprintf(stderr, "STR",
					info.chrootDir.c_str(),
					strerror(e),
					e);
				fflush(stderr);
				_exit(1);
			}

			ret = chdir("STR");
			if (ret == -1) {
				int e = errno;
				fprintf(stderr, "STR",
					strerror(e),
					e);
				fflush(stderr);
				_exit(1);
			}
		}
	}