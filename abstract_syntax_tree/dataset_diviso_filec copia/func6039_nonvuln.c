static void test18(char const* infile,
		   char const* password,
		   char const* outfile,
		   char const* outfile2)
{
    qpdf_read(qpdf, infile, password);
    qpdf_init_write(qpdf, outfile);
    qpdf_set_static_ID(qpdf, QPDF_TRUE);
    qpdf_set_static_aes_IV(qpdf, QPDF_TRUE);
    qpdf_set_r6_encryption_parameters2(
	qpdf, "STR", QPDF_TRUE, QPDF_TRUE,
        QPDF_TRUE, QPDF_TRUE, QPDF_TRUE, QPDF_TRUE,
	qpdf_r3p_low, QPDF_TRUE);
    qpdf_write(qpdf);
    report_errors();
}