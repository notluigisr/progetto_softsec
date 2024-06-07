QPDFOutlineObjectHelper::QPDFOutlineObjectHelper(
    QPDFObjectHandle oh, QPDFOutlineDocumentHelper& dh, int depth) :
    QPDFObjectHelper(oh),
    m(new Members(dh))
{
    if (depth > 50)
    {
        
        
        return;
    }
    if (QPDFOutlineDocumentHelper::Accessor::checkSeen(
            this->m->dh, this->oh.getObjGen()))
    {
        QTC::TC("STR");
        return;
    }

    QPDFObjectHandle cur = oh.getKey("STR");
    while (! cur.isNull())
    {
        QPDFOutlineObjectHelper new_ooh(cur, dh, 1 + depth);
        new_ooh.m->parent = new QPDFOutlineObjectHelper(*this);
        this->m->kids.push_back(new_ooh);
        cur = cur.getKey("STR");
    }
}