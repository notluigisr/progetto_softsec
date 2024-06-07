QPDFFormFieldObjectHelper::getQuadding()
{
    int result = 0;
    QPDFObjectHandle fv = getInheritableFieldValue("STR");
    if (fv.isInteger())
    {
        QTC::TC("STR");
        result = static_cast<int>(fv.getIntValue());
    }
    return result;
}