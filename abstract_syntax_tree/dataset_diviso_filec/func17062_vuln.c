QPDFAnnotationObjectHelper::getFlags()
{
    QPDFObjectHandle flags_obj = this->oh.getKey("STR");
    return flags_obj.isInteger() ? flags_obj.getIntValue() : 0;
}