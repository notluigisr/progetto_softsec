static void v9fs_getattr(void *opaque)
{
    int32_t fid;
    size_t offset = 7;
    ssize_t retval = 0;
    struct stat stbuf;
    V9fsFidState *fidp;
    uint64_t request_mask;
    V9fsStatDotl v9stat_dotl;
    V9fsPDU *pdu = opaque;
    V9fsState *s = pdu->s;

    retval = pdu_unmarshal(pdu, offset, "STR", &fid, &request_mask);
    if (retval < 0) {
        goto out_nofid;
    }
    trace_v9fs_getattr(pdu->tag, pdu->id, fid, request_mask);

    fidp = get_fid(pdu, fid);
    if (fidp == NULL) {
        retval = -ENOENT;
        goto out_nofid;
    }
    
    retval = v9fs_co_lstat(pdu, &fidp->path, &stbuf);
    if (retval < 0) {
        goto out;
    }
    stat_to_v9stat_dotl(s, &stbuf, &v9stat_dotl);

    
    if (request_mask & P9_STATS_GEN) {
        retval = v9fs_co_st_gen(pdu, &fidp->path, stbuf.st_mode, &v9stat_dotl);
        switch (retval) {
        case 0:
            
            v9stat_dotl.st_result_mask |= P9_STATS_GEN;
            break;
        case -EINTR:
            
            goto out;
        default:
            
            break;
        }
    }
    retval = pdu_marshal(pdu, offset, "STR", &v9stat_dotl);
    if (retval < 0) {
        goto out;
    }
    retval += offset;
    trace_v9fs_getattr_return(pdu->tag, pdu->id, v9stat_dotl.st_result_mask,
                              v9stat_dotl.st_mode, v9stat_dotl.st_uid,
                              v9stat_dotl.st_gid);
out:
    put_fid(pdu, fidp);
out_nofid:
    pdu_complete(pdu, retval);
}