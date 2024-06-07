static int ahash_def_finup_finish1(struct ahash_request *req, int err)
{
	if (err)
		goto out;

	req->base.complete = ahash_def_finup_done2;

	err = crypto_ahash_reqtfm(req)->final(req);
	if (err == -EINPROGRESS ||
	    (err == -EBUSY && (ahash_request_flags(req) &
			       CRYPTO_TFM_REQ_MAY_BACKLOG)))
		return err;

out:
	ahash_restore_req(req, err);
	return err;
}