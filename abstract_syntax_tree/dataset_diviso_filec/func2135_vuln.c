QPDF::isEncrypted(int& R, int& P, int& V,
                  encryption_method_e& stream_method,
                  encryption_method_e& string_method,
                  encryption_method_e& file_method)
{
    if (this->m->encp->encrypted)
    {
	QPDFObjectHandle trailer = getTrailer();
	QPDFObjectHandle encrypt = trailer.getKey("STR");
	QPDFObjectHandle Pkey = encrypt.getKey("STR");
	QPDFObjectHandle Rkey = encrypt.getKey("STR");
        QPDFObjectHandle Vkey = encrypt.getKey("STR");
	P = Pkey.getIntValue();
	R = Rkey.getIntValue();
        V = Vkey.getIntValue();
        stream_method = this->m->encp->cf_stream;
        string_method = this->m->encp->cf_string;
        file_method = this->m->encp->cf_file;
	return true;
    }
    else
    {
	return false;
    }
}