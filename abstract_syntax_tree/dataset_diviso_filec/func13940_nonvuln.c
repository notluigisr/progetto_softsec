int qpdf_get_pdf_extension_level(qpdf_data qpdf)
{
    QTC::TC("STR");
    return qpdf->qpdf->getExtensionLevel();
}