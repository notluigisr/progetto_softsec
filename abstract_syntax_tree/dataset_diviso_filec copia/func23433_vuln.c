static int hfi1_file_close(struct inode *inode, struct file *fp)
{
	struct hfi1_filedata *fdata = fp->private_data;
	struct hfi1_ctxtdata *uctxt = fdata->uctxt;
	struct hfi1_devdata *dd = container_of(inode->i_cdev,
					       struct hfi1_devdata,
					       user_cdev);
	unsigned long flags, *ev;

	fp->private_data = NULL;

	if (!uctxt)
		goto done;

	hfi1_cdbg(PROC, "STR", uctxt->ctxt, fdata->subctxt);

	flush_wc();
	
	hfi1_user_sdma_free_queues(fdata, uctxt);

	
	hfi1_put_proc_affinity(fdata->rec_cpu_num);

	
	hfi1_user_exp_rcv_free(fdata);

	
	fdata->uctxt = NULL;
	hfi1_rcd_put(uctxt);

	
	ev = dd->events + uctxt_offset(uctxt) + fdata->subctxt;
	*ev = 0;

	spin_lock_irqsave(&dd->uctxt_lock, flags);
	__clear_bit(fdata->subctxt, uctxt->in_use_ctxts);
	if (!bitmap_empty(uctxt->in_use_ctxts, HFI1_MAX_SHARED_CTXTS)) {
		spin_unlock_irqrestore(&dd->uctxt_lock, flags);
		goto done;
	}
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);

	
	hfi1_rcvctrl(dd, HFI1_RCVCTRL_CTXT_DIS |
		     HFI1_RCVCTRL_TIDFLOW_DIS |
		     HFI1_RCVCTRL_INTRAVAIL_DIS |
		     HFI1_RCVCTRL_TAILUPD_DIS |
		     HFI1_RCVCTRL_ONE_PKT_EGR_DIS |
		     HFI1_RCVCTRL_NO_RHQ_DROP_DIS |
		     HFI1_RCVCTRL_NO_EGR_DROP_DIS |
		     HFI1_RCVCTRL_URGENT_DIS, uctxt);
	
	hfi1_clear_ctxt_jkey(dd, uctxt);
	
	if (uctxt->sc) {
		sc_disable(uctxt->sc);
		set_pio_integrity(uctxt->sc);
	}

	hfi1_free_ctxt_rcv_groups(uctxt);
	hfi1_clear_ctxt_pkey(dd, uctxt);

	uctxt->event_flags = 0;

	deallocate_ctxt(uctxt);
done:
	mmdrop(fdata->mm);

	if (atomic_dec_and_test(&dd->user_refcount))
		complete(&dd->user_comp);

	cleanup_srcu_struct(&fdata->pq_srcu);
	kfree(fdata);
	return 0;
}