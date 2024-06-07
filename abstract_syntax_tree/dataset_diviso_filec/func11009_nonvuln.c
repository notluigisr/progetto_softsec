static void handle_edid_regs(struct mdev_state *mdev_state, u16 offset,
			     char *buf, u32 count, bool is_write)
{
	char *regs = (void *)&mdev_state->edid_regs;

	if (offset + count > sizeof(mdev_state->edid_regs))
		return;
	if (count != 4)
		return;
	if (offset % 4)
		return;

	if (is_write) {
		switch (offset) {
		case offsetof(struct vfio_region_gfx_edid, link_state):
		case offsetof(struct vfio_region_gfx_edid, edid_size):
			memcpy(regs + offset, buf, count);
			break;
		default:
			
			break;
		}
	} else {
		memcpy(buf, regs + offset, count);
	}
}