int oe_getsockopt(
    int sockfd,
    int level,
    int optname,
    void* optval,
    oe_socklen_t* optlen)
{
    int ret = -1;
    oe_fd_t* sock;

    if (!(sock = oe_fdtable_get(sockfd, OE_FD_TYPE_SOCKET)))
        OE_RAISE_ERRNO(oe_errno);

    ret = sock->ops.socket.getsockopt(sock, level, optname, optval, optlen);

done:
    return ret;
}