MultiPartInputFile::Data::checkSharedAttributesValues(const Header & src,
                                                const Header & dst,
                                                vector<string> & conflictingAttributes) const
{
    conflictingAttributes.clear();

    bool conflict = false;

    
    
    
    if (src.displayWindow() != dst.displayWindow())
    {
        conflict = true;
        conflictingAttributes.push_back ("STR");
    }


    
    
    
    if (src.pixelAspectRatio() != dst.pixelAspectRatio())
    {
        conflict = true;
        conflictingAttributes.push_back ("STR");
    }


    
    
    
    const TimeCodeAttribute * srcTimeCode = src.findTypedAttribute<
          TimeCodeAttribute> (TimeCodeAttribute::staticTypeName());
    const TimeCodeAttribute * dstTimeCode = dst.findTypedAttribute<
          TimeCodeAttribute> (TimeCodeAttribute::staticTypeName());

    if (dstTimeCode)
    {
        if  ( (srcTimeCode && (srcTimeCode->value() != dstTimeCode->value())) ||
              (!srcTimeCode))
        {
            conflict = true;
            conflictingAttributes.push_back (TimeCodeAttribute::staticTypeName());
        }
    }

    
    
    
    const ChromaticitiesAttribute * srcChrom =  src.findTypedAttribute<
          ChromaticitiesAttribute> (ChromaticitiesAttribute::staticTypeName());
    const ChromaticitiesAttribute * dstChrom =  dst.findTypedAttribute<
          ChromaticitiesAttribute> (ChromaticitiesAttribute::staticTypeName());

    if (dstChrom)
    {
        if ( (srcChrom && (srcChrom->value() != dstChrom->value())) ||
             (!srcChrom))
        {
            conflict = true;
            conflictingAttributes.push_back (ChromaticitiesAttribute::staticTypeName());
        }
    }


    return conflict;
}