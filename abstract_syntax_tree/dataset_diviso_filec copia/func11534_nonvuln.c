void qpdf_set_content_normalization(qpdf_data qpdf, QPDF_BOOL value)
{
    QTC::TC("STR");
    qpdf->qpdf_writer->setContentNormalization(value);
}