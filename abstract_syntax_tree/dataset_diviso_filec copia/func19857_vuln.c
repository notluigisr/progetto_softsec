static ssize_t _hostsock_recvmsg(
    oe_fd_t* sock_,
    struct oe_msghdr* msg,
    int flags)
{
    ssize_t ret = -1;
    sock_t* sock = _cast_sock(sock_);
    oe_errno = 0;
    void* buf = NULL;
    size_t buf_size = 0;

    
    if (!sock || !msg || (msg->msg_iovlen && !msg->msg_iov))
        OE_RAISE_ERRNO(OE_EINVAL);

    
    if (oe_iov_pack(msg->msg_iov, (int)msg->msg_iovlen, &buf, &buf_size) != 0)
        OE_RAISE_ERRNO(OE_ENOMEM);

    
    {
        if (oe_syscall_recvmsg_ocall(
                &ret,
                sock->host_fd,
                msg->msg_name,
                msg->msg_namelen,
                &msg->msg_namelen,
                buf,
                msg->msg_iovlen,
                buf_size,
                msg->msg_control,
                msg->msg_controllen,
                &msg->msg_controllen,
                flags) != OE_OK)
        {
            OE_RAISE_ERRNO(OE_EINVAL);
        }

        if (ret == -1)
            OE_RAISE_ERRNO(oe_errno);
    }

    
    if (oe_iov_sync(msg->msg_iov, (int)msg->msg_iovlen, buf, buf_size) != 0)
        OE_RAISE_ERRNO(OE_EINVAL);

done:

    if (buf)
        oe_free(buf);

    return ret;
}