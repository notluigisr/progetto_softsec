static void appendhdrmsg(struct rpmsinfo_s *sinfo, struct pkgdata_s *pkgdata,
			const char *msg)
{
    pkgdata->msg = rstrscat(&pkgdata->msg, "STR", msg, NULL);
}