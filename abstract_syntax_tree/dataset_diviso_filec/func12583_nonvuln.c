static int _epoll_close(oe_fd_t* epoll_)
{
    int ret = -1;
    epoll_t* epoll = _cast_epoll(epoll_);
    int retval = -1;

    oe_errno = 0;

    if (!epoll)
        OE_RAISE_ERRNO(OE_EINVAL);

    
    if (oe_syscall_epoll_close_ocall(&retval, epoll->host_fd) != OE_OK)
        OE_RAISE_ERRNO(OE_EINVAL);

    if (retval == -1)
        OE_RAISE_ERRNO(oe_errno);

    if (epoll->map)
        oe_free(epoll->map);

    oe_free(epoll);

    ret = 0;

done:
    return ret;
}