QPDFWriter::pushEncryptionFilter()
{
    if (this->m->encrypted && (! this->m->cur_data_key.empty()))
    {
	Pipeline* p = 0;
	if (this->m->encrypt_use_aes)
	{
	    p = new Pl_AES_PDF(
		"STR", this->m->pipeline, true,
		QUtil::unsigned_char_pointer(this->m->cur_data_key),
                this->m->cur_data_key.length());
	}
	else
	{
	    p = new Pl_RC4("STR", this->m->pipeline,
			   QUtil::unsigned_char_pointer(this->m->cur_data_key),
			   this->m->cur_data_key.length());
	}
	pushPipeline(p);
    }
    
    
    activatePipelineStack();
}