QPDFObjectHandle::newReal(double value, int decimal_places)
{
    return QPDFObjectHandle(new QPDF_Real(value, decimal_places));
}