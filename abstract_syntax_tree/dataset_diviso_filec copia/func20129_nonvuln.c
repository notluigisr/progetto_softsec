off_t fstat_st_size_or_die(int fd)
{
    struct stat statbuf;
    if (fstat(fd, &statbuf))
        perror_msg_and_die("STR");
    return statbuf.st_size;
}