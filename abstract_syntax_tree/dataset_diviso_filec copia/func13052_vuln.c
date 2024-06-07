local int decode(struct state *s, struct huffman *h)
{
    int len;            
    int code;           
    int first;          
    int count;          
    int index;          
    int bitbuf;         
    int left;           
	 boost::int16_t *next;        

    bitbuf = s->bitbuf;
    left = s->bitcnt;
    code = first = index = 0;
    len = 1;
    next = h->count + 1;
    while (1) {
        while (left--) {
            code |= bitbuf & 1;
            bitbuf >>= 1;
            count = *next++;
            if (code < first + count) { 
                s->bitbuf = bitbuf;
                s->bitcnt = (s->bitcnt - len) & 7;
                return h->symbol[index + (code - first)];
            }
            index += count;             
            first += count;
            first <<= 1;
            code <<= 1;
            len++;
        }
        left = (MAXBITS+1) - len;
        if (left == 0) break;
        if (s->incnt == s->inlen) longjmp(s->env, 1);   
        bitbuf = s->in[s->incnt++];
        if (left > 8) left = 8;
    }
    return -9;                          
}