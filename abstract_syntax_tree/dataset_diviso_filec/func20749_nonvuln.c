query_io (struct query *z, iopause_fd *x, struct taia *deadline)
{
    qmerge_io (z->qm, x, deadline);
}