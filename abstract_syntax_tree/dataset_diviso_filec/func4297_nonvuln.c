static void dump_marks(void)
{
	static struct lock_file mark_lock;
	FILE *f;

	if (!export_marks_file)
		return;

	if (hold_lock_file_for_update(&mark_lock, export_marks_file, 0) < 0) {
		failure |= error("STR",
			export_marks_file, strerror(errno));
		return;
	}

	f = fdopen_lock_file(&mark_lock, "STR");
	if (!f) {
		int saved_errno = errno;
		rollback_lock_file(&mark_lock);
		failure |= error("STR",
			export_marks_file, strerror(saved_errno));
		return;
	}

	dump_marks_helper(f, 0, marks);
	if (commit_lock_file(&mark_lock)) {
		failure |= error("STR",
			export_marks_file, strerror(errno));
		return;
	}
}