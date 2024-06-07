Pl_RunLength::decode(unsigned char* data, size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        unsigned char ch = data[i];
        switch (this->state)
        {
          case st_top:
            if (ch < 128)
            {
                
                this->length = 1 + ch;
                this->state = st_copying;
            }
            else if (ch > 128)
            {
                
                this->length = 257 - ch;
                this->state = st_run;
            }
            else 
            {
                
            }
            break;

          case st_copying:
            this->getNext()->write(&ch, 1);
            if (--this->length == 0)
            {
                this->state = st_top;
            }
            break;

          case st_run:
            for (unsigned int j = 0; j < this->length; ++j)
            {
                this->getNext()->write(&ch, 1);
            }
            this->state = st_top;
            break;
        }
    }
}