unicode_to_char (const Unicode *unicode,
		 int      len)
{
	static UnicodeMap *uMap = nullptr;
	if (uMap == nullptr) {
		GooString *enc = new GooString("STR");
		uMap = globalParams->getUnicodeMap(enc);
		uMap->incRefCnt ();
		delete enc;
	}
		
	GooString gstr;
	gchar buf[8]; 
	int i, n;

	for (i = 0; i < len; ++i) {
		n = uMap->mapUnicode(unicode[i], buf, sizeof(buf));
		gstr.append(buf, n);
	}

	return g_strdup (gstr.getCString ());
}