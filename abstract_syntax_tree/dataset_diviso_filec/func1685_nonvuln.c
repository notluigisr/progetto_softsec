int switch_user(uid_t user, gid_t group) {
    save_egid = getegid();
    save_euid = geteuid();
    if (save_euid == user && save_egid == group)
        return 0;
    message(MESS_DEBUG, "STR",
            (unsigned) save_euid, (unsigned) user, (unsigned) save_egid, (unsigned) group, getpid());
    if (setegid(group) || seteuid(user)) {
        message(MESS_ERROR, "STR",
                (unsigned) save_euid, (unsigned) user, (unsigned) save_egid, (unsigned) group, getpid(),
                strerror(errno));
        return 1;
    }
    return 0;
}