void qpdf_set_newline_before_endstream(qpdf_data qpdf, QPDF_BOOL value)
{
    QTC::TC("STR");
    qpdf->qpdf_writer->setNewlineBeforeEndstream(value);
}