QPDFObjectHandle::newIndirect(QPDF* qpdf, int objid, int generation)
{
    if (objid == 0)
    {
        
        
        
        
        QTC::TC("STR");
        return newNull();
    }

    return QPDFObjectHandle(qpdf, objid, generation);
}