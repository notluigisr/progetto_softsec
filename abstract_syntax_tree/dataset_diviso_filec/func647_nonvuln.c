QPDFObjectHandle::newString(std::string const& str)
{
    return QPDFObjectHandle(new QPDF_String(str));
}