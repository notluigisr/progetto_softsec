SMB2_write(const unsigned int xid, struct cifs_io_parms *io_parms,
	   unsigned int *nbytes, struct kvec *iov, int n_vec)
{
	struct smb_rqst rqst;
	int rc = 0;
	struct smb2_write_req *req = NULL;
	struct smb2_write_rsp *rsp = NULL;
	int resp_buftype;
	struct kvec rsp_iov;
	int flags = 0;
	unsigned int total_len;

	*nbytes = 0;

	if (n_vec < 1)
		return rc;

	rc = smb2_plain_req_init(SMB2_WRITE, io_parms->tcon, (void **) &req,
			     &total_len);
	if (rc)
		return rc;

	if (io_parms->tcon->ses->server == NULL)
		return -ECONNABORTED;

	if (smb3_encryption_required(io_parms->tcon))
		flags |= CIFS_TRANSFORM_REQ;

	req->sync_hdr.ProcessId = cpu_to_le32(io_parms->pid);

	req->PersistentFileId = io_parms->persistent_fid;
	req->VolatileFileId = io_parms->volatile_fid;
	req->WriteChannelInfoOffset = 0;
	req->WriteChannelInfoLength = 0;
	req->Channel = 0;
	req->Length = cpu_to_le32(io_parms->length);
	req->Offset = cpu_to_le64(io_parms->offset);
	req->DataOffset = cpu_to_le16(
				offsetof(struct smb2_write_req, Buffer));
	req->RemainingBytes = 0;

	trace_smb3_write_enter(xid, io_parms->persistent_fid,
		io_parms->tcon->tid, io_parms->tcon->ses->Suid,
		io_parms->offset, io_parms->length);

	iov[0].iov_base = (char *)req;
	
	iov[0].iov_len = total_len - 1;

	memset(&rqst, 0, sizeof(struct smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = n_vec + 1;

	rc = cifs_send_recv(xid, io_parms->tcon->ses, &rqst,
			    &resp_buftype, flags, &rsp_iov);
	cifs_small_buf_release(req);
	rsp = (struct smb2_write_rsp *)rsp_iov.iov_base;

	if (rc) {
		trace_smb3_write_err(xid, req->PersistentFileId,
				     io_parms->tcon->tid,
				     io_parms->tcon->ses->Suid,
				     io_parms->offset, io_parms->length, rc);
		cifs_stats_fail_inc(io_parms->tcon, SMB2_WRITE_HE);
		cifs_dbg(VFS, "STR", rc);
	} else {
		*nbytes = le32_to_cpu(rsp->DataLength);
		trace_smb3_write_done(xid, req->PersistentFileId,
				     io_parms->tcon->tid,
				     io_parms->tcon->ses->Suid,
				     io_parms->offset, *nbytes);
	}

	free_rsp_buf(resp_buftype, rsp);
	return rc;
}