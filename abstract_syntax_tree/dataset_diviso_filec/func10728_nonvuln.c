static void call_read(qpdf_data qpdf)
{
    qpdf->qpdf->processFile(qpdf->filename, qpdf->password);
}