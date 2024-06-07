QPDF_ERROR_CODE qpdf_init_write_memory(qpdf_data qpdf)
{
    qpdf_init_write_internal(qpdf);
    QPDF_ERROR_CODE status = trap_errors(qpdf, &call_init_write_memory);
    QTC::TC("STR");
    qpdf->write_memory = true;
    return status;
}