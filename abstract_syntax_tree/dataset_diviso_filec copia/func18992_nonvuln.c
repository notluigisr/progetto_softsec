static void test02(char const* infile,
		   char const* password,
		   char const* outfile,
		   char const* outfile2)
{
    qpdf_set_suppress_warnings(qpdf, QPDF_TRUE);
    if (((qpdf_read(qpdf, infile, password) & QPDF_ERRORS) == 0) &&
	((qpdf_init_write(qpdf, outfile) & QPDF_ERRORS) == 0))
    {
	qpdf_set_static_ID(qpdf, QPDF_TRUE);
	qpdf_write(qpdf);
    }
    report_errors();
}