QPDFFormFieldObjectHelper::setCheckBoxValue(bool value)
{
    
    QPDFObjectHandle name =
        QPDFObjectHandle::newName(value ? "STR");
    setFieldAttribute("STR", name);
    QPDFObjectHandle AP = this->oh.getKey("STR");
    QPDFObjectHandle annot;
    if (AP.isNull())
    {
        
        
        QPDFObjectHandle kids = this->oh.getKey("STR");
        if (kids.isArray())
        {
            int nkids = kids.getArrayNItems();
            for (int i = 0; i < nkids; ++i)
            {
                QPDFObjectHandle kid = kids.getArrayItem(i);
                AP = kid.getKey("STR");
                if (! AP.isNull())
                {
                    QTC::TC("STR");
                    annot = kid;
                    break;
                }
            }
        }
    }
    else
    {
        annot = this->oh;
    }
    if (! annot.isInitialized())
    {
        QTC::TC("STR");
        this->oh.warnIfPossible(
            "STR");
        return;
    }
    QTC::TC("STR");
    annot.replaceKey("STR", name);
}