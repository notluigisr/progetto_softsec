static int check_ext_ctrls(struct v4l2_ext_controls *c, int allow_priv)
{
	__u32 i;

	
	c->reserved[0] = 0;
	for (i = 0; i < c->count; i++)
		c->controls[i].reserved2[0] = 0;

	
	if (!allow_priv && c->which == V4L2_CID_PRIVATE_BASE)
		return 0;
	if (!c->which)
		return 1;
	
	for (i = 0; i < c->count; i++) {
		if (V4L2_CTRL_ID2WHICH(c->controls[i].id) != c->which) {
			c->error_idx = i;
			return 0;
		}
	}
	return 1;
}