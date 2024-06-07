static void qd_unlock(struct gfs2_quota_data *qd)
{
	gfs2_assert_warn(qd->qd_gl->gl_sbd,
			 test_bit(QDF_LOCKED, &qd->qd_flags));
	clear_bit(QDF_LOCKED, &qd->qd_flags);
	bh_put(qd);
	slot_put(qd);
	qd_put(qd);
}