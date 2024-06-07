local int stored(struct state *s)
{
    unsigned len;       

    
    s->bitbuf = 0;
    s->bitcnt = 0;

    
    if (s->incnt + 4 > s->inlen) return 2;      
    len = s->in[s->incnt++];
    len |= s->in[s->incnt++] << 8;
    if (s->in[s->incnt++] != (~len & 0xff) ||
        s->in[s->incnt++] != ((~len >> 8) & 0xff))
        return -2;                              

    
    if (s->incnt + len > s->inlen) return 2;    
    if (s->out != NIL) {
        if (s->outcnt + len > s->outlen)
            return 1;                           
        while (len--)
            s->out[s->outcnt++] = s->in[s->incnt++];
    }
    else {                                      
        s->outcnt += len;
        s->incnt += len;
    }

    
    return 0;
}