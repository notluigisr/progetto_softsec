QPDF::getExtensionLevel()
{
    int result = 0;
    QPDFObjectHandle obj = getRoot();
    if (obj.hasKey("STR"))
    {
        obj = obj.getKey("STR");
        if (obj.isDictionary() && obj.hasKey("STR"))
        {
            obj = obj.getKey("STR");
            if (obj.isDictionary() && obj.hasKey("STR"))
            {
                obj = obj.getKey("STR");
                if (obj.isInteger())
                {
                    result = obj.getIntValue();
                }
            }
        }
    }
    return result;
}