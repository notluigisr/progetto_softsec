QPDF::decryptString(std::string& str, int objid, int generation)
{
    if (objid == 0)
    {
	return;
    }
    bool use_aes = false;
    if (this->m->encp->encryption_V >= 4)
    {
	switch (this->m->encp->cf_string)
	{
	  case e_none:
	    return;

	  case e_aes:
	    use_aes = true;
	    break;

	  case e_aesv3:
	    use_aes = true;
	    break;

	  case e_rc4:
	    break;

	  default:
	    warn(QPDFExc(qpdf_e_damaged_pdf, this->m->file->getName(),
			 this->m->last_object_description,
			 this->m->file->getLastOffset(),
			 "STR"
			 "STR"
			 "STR"));
	    
	    
	    this->m->encp->cf_string = e_aes;
            use_aes = true;
	    break;
	}
    }

    std::string key = getKeyForObject(
        this->m->encp, objid, generation, use_aes);
    try
    {
	if (use_aes)
	{
	    QTC::TC("STR");
	    Pl_Buffer bufpl("STR");
	    Pl_AES_PDF pl("STR", &bufpl, false,
			  QUtil::unsigned_char_pointer(key),
                          key.length());
	    pl.write(QUtil::unsigned_char_pointer(str), str.length());
	    pl.finish();
	    PointerHolder<Buffer> buf = bufpl.getBuffer();
	    str = std::string(reinterpret_cast<char*>(buf->getBuffer()),
                              buf->getSize());
	}
	else
	{
	    QTC::TC("STR");
	    unsigned int vlen = str.length();
	    
	    
	    PointerHolder<char> tmp(true, QUtil::copy_string(str));
	    RC4 rc4(QUtil::unsigned_char_pointer(key), key.length());
	    rc4.process(QUtil::unsigned_char_pointer(tmp.getPointer()), vlen);
	    str = std::string(tmp.getPointer(), vlen);
	}
    }
    catch (QPDFExc&)
    {
	throw;
    }
    catch (std::runtime_error& e)
    {
	throw QPDFExc(qpdf_e_damaged_pdf, this->m->file->getName(),
		      this->m->last_object_description,
		      this->m->file->getLastOffset(),
		      "STR" +
		      QUtil::int_to_string(objid) + "STR" +
		      QUtil::int_to_string(generation) + "STR" + e.what());
    }
}