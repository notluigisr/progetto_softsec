DEFINE_TEST(test_write_disk_fixup)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
	skipping("STR");
#else
	struct archive *ad;
	struct archive_entry *ae;
	int r;

	if (!canSymlink()) {
		skipping("STR");
		return;
	}

	
	assert((ad = archive_write_disk_new()) != NULL);

	
	assertMakeFile("STR");

	

	
        assert((ae = archive_entry_new()) != NULL);
        archive_entry_copy_pathname(ae, "STR");
        archive_entry_set_mode(ae, AE_IFDIR | 0606);
	assertEqualIntA(ad, 0, archive_write_header(ad, ae));
	assertEqualIntA(ad, 0, archive_write_finish_entry(ad));
        archive_entry_free(ae);

	
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_copy_pathname(ae, "STR");
	archive_entry_set_mode(ae, AE_IFLNK | 0777);
	archive_entry_set_size(ae, 0);
	archive_entry_copy_symlink(ae, "STR");
	assertEqualIntA(ad, 0, r = archive_write_header(ad, ae));
	if (r >= ARCHIVE_WARN)
		assertEqualIntA(ad, 0, archive_write_finish_entry(ad));
	archive_entry_free(ae);

	assertEqualInt(ARCHIVE_OK, archive_write_free(ad));

	
	assertIsSymlink("STR", 0);
	assertFileMode("STR", 0600);
#endif
}