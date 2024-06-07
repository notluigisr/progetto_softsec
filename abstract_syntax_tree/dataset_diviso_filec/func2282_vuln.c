QPDFWriter::copyEncryptionParameters(QPDF& qpdf)
{
    this->m->preserve_encryption = false;
    QPDFObjectHandle trailer = qpdf.getTrailer();
    if (trailer.hasKey("STR"))
    {
        generateID();
        this->m->id1 =
            trailer.getKey("STR").getArrayItem(0).getStringValue();
	QPDFObjectHandle encrypt = trailer.getKey("STR");
	int V = encrypt.getKey("STR").getIntValue();
	int key_len = 5;
	if (V > 1)
	{
	    key_len = encrypt.getKey("STR").getIntValue() / 8;
	}
	if (encrypt.hasKey("STR") &&
	    encrypt.getKey("STR").isBool())
	{
	    this->m->encrypt_metadata =
		encrypt.getKey("STR").getBoolValue();
	}
        if (V >= 4)
        {
            
            
            
            
            
            
            this->m->encrypt_use_aes = true;
        }
	QTC::TC("STR",
		this->m->encrypt_metadata ? 0 : 1);
        QTC::TC("STR",
                this->m->encrypt_use_aes ? 0 : 1);
        std::string OE;
        std::string UE;
        std::string Perms;
        std::string encryption_key;
        if (V >= 5)
        {
            QTC::TC("STR");
	    OE = encrypt.getKey("STR").getStringValue();
            UE = encrypt.getKey("STR").getStringValue();
	    Perms = encrypt.getKey("STR").getStringValue();
            encryption_key = qpdf.getEncryptionKey();
        }

	setEncryptionParametersInternal(
	    V,
	    encrypt.getKey("STR").getIntValue(),
    	    key_len,
	    encrypt.getKey("STR").getIntValue(),
	    encrypt.getKey("STR").getStringValue(),
	    encrypt.getKey("STR").getStringValue(),
            OE,
            UE,
            Perms,
	    this->m->id1,		
	    qpdf.getPaddedUserPassword(),
            encryption_key);
    }
}