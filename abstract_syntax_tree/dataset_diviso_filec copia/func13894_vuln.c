void preproc_mount_mnt_dir(void) {
	
	if (!tmpfs_mounted) {
		if (arg_debug)
			printf("STR", RUN_MNT_DIR);
		if (mount("STR") < 0)
			errExit("STR");
		tmpfs_mounted = 1;
		fs_logger2("STR", RUN_MNT_DIR);

#ifdef HAVE_SECCOMP
		if (arg_seccomp_block_secondary)
			copy_file(PATH_SECCOMP_BLOCK_SECONDARY, RUN_SECCOMP_BLOCK_SECONDARY, getuid(), getgid(), 0644); 
		else {
			
			copy_file(PATH_SECCOMP_32, RUN_SECCOMP_32, getuid(), getgid(), 0644); 
		}
		if (arg_allow_debuggers)
			copy_file(PATH_SECCOMP_DEFAULT_DEBUG, RUN_SECCOMP_CFG, getuid(), getgid(), 0644); 
		else
			copy_file(PATH_SECCOMP_DEFAULT, RUN_SECCOMP_CFG, getuid(), getgid(), 0644); 

		if (arg_memory_deny_write_execute)
			copy_file(PATH_SECCOMP_MDWX, RUN_SECCOMP_MDWX, getuid(), getgid(), 0644); 
		
		create_empty_file_as_root(RUN_SECCOMP_PROTOCOL, 0644);
		if (set_perms(RUN_SECCOMP_PROTOCOL, getuid(), getgid(), 0644))
			errExit("STR");
		create_empty_file_as_root(RUN_SECCOMP_POSTEXEC, 0644);
		if (set_perms(RUN_SECCOMP_POSTEXEC, getuid(), getgid(), 0644))
			errExit("STR");
#endif
	}
}