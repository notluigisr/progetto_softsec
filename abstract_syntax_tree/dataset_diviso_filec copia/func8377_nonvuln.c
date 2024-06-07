static void rbd_set_owner_cid(struct rbd_device *rbd_dev,
			      const struct rbd_client_id *cid)
{
	dout("STR", __func__, rbd_dev,
	     rbd_dev->owner_cid.gid, rbd_dev->owner_cid.handle,
	     cid->gid, cid->handle);
	rbd_dev->owner_cid = *cid; 
}