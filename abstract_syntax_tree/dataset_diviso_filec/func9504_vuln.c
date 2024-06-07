QPDFFormFieldObjectHelper::getFlags()
{
    QPDFObjectHandle f = getInheritableFieldValue("STR");
    return f.isInteger() ? f.getIntValue() : 0;
}