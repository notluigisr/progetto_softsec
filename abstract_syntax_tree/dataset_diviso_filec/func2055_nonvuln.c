static int rbd_img_fill_from_bvecs(struct rbd_img_request *img_req,
				   struct ceph_file_extent *img_extents,
				   u32 num_img_extents,
				   struct bio_vec *bvecs)
{
	struct ceph_bvec_iter it = {
		.bvecs = bvecs,
		.iter = { .bi_size = ceph_file_extents_bytes(img_extents,
							     num_img_extents) },
	};

	return __rbd_img_fill_from_bvecs(img_req, img_extents, num_img_extents,
					 &it);
}