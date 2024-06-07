QPDFObjectHandle newInteger(size_t val)
{
    return QPDFObjectHandle::newInteger(QIntC::to_int(val));
}