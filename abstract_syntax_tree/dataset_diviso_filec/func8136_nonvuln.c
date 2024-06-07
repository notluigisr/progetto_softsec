static void quotad_error(struct gfs2_sbd *sdp, const char *msg, int error)
{
	if (error == 0 || error == -EROFS)
		return;
	if (!test_bit(SDF_SHUTDOWN, &sdp->sd_flags))
		fs_err(sdp, "STR", msg, error);
}