accumulate_int(struct interface *ifp, unsigned int value)
{
    babel_interface_nfo *babel_ifp = babel_get_if_nfo(ifp);
    DO_HTONL(babel_ifp->sendbuf + babel_ifp->buffered, value);
    babel_ifp->buffered += 4;
}