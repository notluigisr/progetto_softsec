static int aio_prep_rw(struct kiocb *req, const struct iocb *iocb)
{
	int ret;

	req->ki_filp = fget(iocb->aio_fildes);
	if (unlikely(!req->ki_filp))
		return -EBADF;
	req->ki_complete = aio_complete_rw;
	req->private = NULL;
	req->ki_pos = iocb->aio_offset;
	req->ki_flags = iocb_flags(req->ki_filp);
	if (iocb->aio_flags & IOCB_FLAG_RESFD)
		req->ki_flags |= IOCB_EVENTFD;
	req->ki_hint = ki_hint_validate(file_write_hint(req->ki_filp));
	if (iocb->aio_flags & IOCB_FLAG_IOPRIO) {
		
		ret = ioprio_check_cap(iocb->aio_reqprio);
		if (ret) {
			pr_debug("STR", ret);
			goto out_fput;
		}

		req->ki_ioprio = iocb->aio_reqprio;
	} else
		req->ki_ioprio = get_current_ioprio();

	ret = kiocb_set_rw_flags(req, iocb->aio_rw_flags);
	if (unlikely(ret))
		goto out_fput;

	req->ki_flags &= ~IOCB_HIPRI; 
	return 0;

out_fput:
	fput(req->ki_filp);
	return ret;
}