Header::writeTo (OPENEXR_IMF_INTERNAL_NAMESPACE::OStream &os, bool isTiled) const
{
    
    
    
    

    int version = EXR_VERSION;

    
    
    
    

    Int64 previewPosition = 0;

    const Attribute *preview =
	    findTypedAttribute <PreviewImageAttribute> ("STR");

    for (ConstIterator i = begin(); i != end(); ++i)
    {
	
	
	

	OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::write <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (os, i.name());
	OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::write <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (os, i.attribute().typeName());

	
	
	
	

	StdOSStream oss;
	i.attribute().writeValueTo (oss, version);

	std::string s = oss.str();
	OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::write <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (os, (int) s.length());

	if (&i.attribute() == preview)
	    previewPosition = os.tellp();

	os.write (s.data(), int(s.length()));
    }

    
    
    

    OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::write <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (os, "");

    return previewPosition;
}