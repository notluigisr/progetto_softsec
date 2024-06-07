Pl_AES_PDF::finish()
{
    if (this->encrypt)
    {
	if (this->offset == this->buf_size)
	{
	    flush(false);
	}
        if (! this->disable_padding)
        {
            
            
            
            unsigned char pad =
                static_cast<unsigned char>(this->buf_size - this->offset);
            memset(this->inbuf + this->offset, pad, pad);
            this->offset = this->buf_size;
            flush(false);
        }
    }
    else
    {
	if (this->offset != this->buf_size)
	{
	    
	    
	    
	    
	    
	    assert(this->buf_size > this->offset);
	    std::memset(this->inbuf + this->offset, 0,
			this->buf_size - this->offset);
	    this->offset = this->buf_size;
	}
	flush(! this->disable_padding);
    }
    getNext()->finish();
}