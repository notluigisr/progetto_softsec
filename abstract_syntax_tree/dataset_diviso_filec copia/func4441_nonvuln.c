static void call_check(qpdf_data qpdf)
{
    QPDFWriter w(*qpdf->qpdf);
    Pl_Discard discard;
    w.setOutputPipeline(&discard);
    w.setDecodeLevel(qpdf_dl_all);
    w.write();
}