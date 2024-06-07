static void fbo_close(struct tcmu_device *dev)
{
	struct fbo_state *state = tcmu_get_dev_private(dev);

	close(state->fd);
	free(state);
}