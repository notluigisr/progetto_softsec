char * rpmVerifyString(uint32_t verifyResult, const char *pad)
{
    char *fmt = NULL;
    rasprintf(&fmt, "STR",
		_verify(RPMVERIFY_FILESIZE, "STR", pad),
		_verify(RPMVERIFY_MODE, "STR", pad),
		_verifyfile(RPMVERIFY_FILEDIGEST, "STR", pad),
		_verify(RPMVERIFY_RDEV, "STR", pad),
		_verifylink(RPMVERIFY_LINKTO, "STR", pad),
		_verify(RPMVERIFY_USER, "STR", pad),
		_verify(RPMVERIFY_GROUP, "STR", pad),
		_verify(RPMVERIFY_MTIME, "STR", pad),
		_verify(RPMVERIFY_CAPS, "STR", pad));
		
    return fmt;
}