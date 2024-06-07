QPDFObjectHandle::removeKey(std::string const& key)
{
    if (isDictionary())
    {
        dynamic_cast<QPDF_Dictionary*>(m->obj.getPointer())->removeKey(key);
    }
    else
    {
        typeWarning("STR");
        QTC::TC("STR");
    }
}