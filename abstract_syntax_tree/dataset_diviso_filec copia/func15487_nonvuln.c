int oe_accept(int sockfd, struct oe_sockaddr* addr, oe_socklen_t* addrlen)
{
    oe_fd_t* sock;
    oe_fd_t* new_sock = NULL;
    int ret = -1;

    if (!(sock = oe_fdtable_get(sockfd, OE_FD_TYPE_SOCKET)))
        OE_RAISE_ERRNO(oe_errno);

    if ((new_sock = sock->ops.socket.accept(sock, addr, addrlen)) == NULL)
        OE_RAISE_ERRNO(oe_errno);

    if ((ret = oe_fdtable_assign(new_sock)) == -1)
        OE_RAISE_ERRNO(oe_errno);

    new_sock = NULL;

done:

    if (new_sock)
        new_sock->ops.fd.close(new_sock);

    return ret;
}