QPDF::getObjectCount()
{
    
    
    
    
    fixDanglingReferences();
    QPDFObjGen og(0, 0);
    if (! this->m->obj_cache.empty())
    {
	og = (*(this->m->obj_cache.rbegin())).first;
    }
    return og.getObj();
}