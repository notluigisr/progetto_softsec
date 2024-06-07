static int get_ctxt_info(struct hfi1_filedata *fd, unsigned long arg, u32 len)
{
	struct hfi1_ctxt_info cinfo;
	struct hfi1_ctxtdata *uctxt = fd->uctxt;

	if (sizeof(cinfo) != len)
		return -EINVAL;

	memset(&cinfo, 0, sizeof(cinfo));
	cinfo.runtime_flags = (((uctxt->flags >> HFI1_CAP_MISC_SHIFT) &
				HFI1_CAP_MISC_MASK) << HFI1_CAP_USER_SHIFT) |
			HFI1_CAP_UGET_MASK(uctxt->flags, MASK) |
			HFI1_CAP_KGET_MASK(uctxt->flags, K2U);
	
	if (!fd->use_mn)
		cinfo.runtime_flags |= HFI1_CAP_TID_UNMAP; 

	cinfo.num_active = hfi1_count_active_units();
	cinfo.unit = uctxt->dd->unit;
	cinfo.ctxt = uctxt->ctxt;
	cinfo.subctxt = fd->subctxt;
	cinfo.rcvtids = roundup(uctxt->egrbufs.alloced,
				uctxt->dd->rcv_entries.group_size) +
		uctxt->expected_count;
	cinfo.credits = uctxt->sc->credits;
	cinfo.numa_node = uctxt->numa_id;
	cinfo.rec_cpu = fd->rec_cpu_num;
	cinfo.send_ctxt = uctxt->sc->hw_context;

	cinfo.egrtids = uctxt->egrbufs.alloced;
	cinfo.rcvhdrq_cnt = get_hdrq_cnt(uctxt);
	cinfo.rcvhdrq_entsize = get_hdrqentsize(uctxt) << 2;
	cinfo.sdma_ring_size = fd->cq->nentries;
	cinfo.rcvegr_size = uctxt->egrbufs.rcvtid_size;

	trace_hfi1_ctxt_info(uctxt->dd, uctxt->ctxt, fd->subctxt, &cinfo);
	if (copy_to_user((void __user *)arg, &cinfo, len))
		return -EFAULT;

	return 0;
}