static inline bool ioat_reset_pending(struct ioat_chan_common *chan)
{
	u8 ver = chan->device->version;
	u8 cmd;

	cmd = readb(chan->reg_base + IOAT_CHANCMD_OFFSET(ver));
	return (cmd & IOAT_CHANCMD_RESET) == IOAT_CHANCMD_RESET;
}