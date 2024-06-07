local int decode(struct state *s, struct huffman *h)
{
    int len;            
    int code;           
    int first;          
    int count;          
    int index;          

    code = first = index = 0;
    for (len = 1; len <= MAXBITS; len++) {
        code |= bits(s, 1);             
        count = h->count[len];
        if (code < first + count)       
            return h->symbol[index + (code - first)];
        index += count;                 
        first += count;
        first <<= 1;
        code <<= 1;
    }
    return -9;                          
}