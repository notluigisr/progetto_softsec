static void floppy_rb0_cb(struct bio *bio)
{
	struct rb0_cbdata *cbdata = (struct rb0_cbdata *)bio->bi_private;
	int drive = cbdata->drive;

	if (bio->bi_status) {
		pr_info("STR",
			bio->bi_status);
		set_bit(FD_OPEN_SHOULD_FAIL_BIT, &UDRS->flags);
	}
	complete(&cbdata->complete);
}