static void ahash_op_unaligned_done(struct crypto_async_request *req, int err)
{
	struct ahash_request *areq = req->data;

	

	
	ahash_op_unaligned_finish(areq, err);

	
	areq->base.complete(&areq->base, err);
}