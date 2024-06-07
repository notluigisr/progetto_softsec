static void ahash_restore_req(struct ahash_request *req)
{
	struct ahash_request_priv *priv = req->priv;

	
	req->result = priv->result;
	req->base.complete = priv->complete;
	req->base.data = priv->data;
	req->priv = NULL;

	
	kzfree(priv);
}