ensure_space(struct interface *ifp, int space)
{
    babel_interface_nfo *babel_ifp = babel_get_if_nfo(ifp);
    if(babel_ifp->bufsize - babel_ifp->buffered < space)
        flushbuf(ifp);
}