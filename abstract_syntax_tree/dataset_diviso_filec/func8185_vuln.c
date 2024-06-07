int puff(unsigned char *dest,           
         boost::uint32_t *destlen,        
         const unsigned char *source,         
         boost::uint32_t *sourcelen)      
{
    struct state s;             
    int last, type;             
    int err;                    

    
    s.out = dest;
    s.outlen = *destlen;                
    s.outcnt = 0;

    
    s.in = source;
    s.inlen = *sourcelen;
    s.incnt = 0;
    s.bitbuf = 0;
    s.bitcnt = 0;

    
    if (setjmp(s.env) != 0)             
        err = 2;                        
    else {
        
        do {
            last = bits(&s, 1);         
            type = bits(&s, 2);         
            err = type == 0 ? stored(&s) :
                  (type == 1 ? fixed(&s) :
                   (type == 2 ? dynamic(&s) :
                    -1));               
            if (err != 0) break;        
        } while (!last);
    }

    
    if (err <= 0) {
        *destlen = s.outcnt;
        *sourcelen = s.incnt;
    }
    return err;
}