local int construct(struct huffman *h, boost::int16_t *length, int n)
{
    int symbol;         
    int len;            
    int left;           
	 boost::int16_t offs[MAXBITS+1];      

    
    for (len = 0; len <= MAXBITS; len++)
        h->count[len] = 0;
    for (symbol = 0; symbol < n; symbol++)
        (h->count[length[symbol]])++;   
    if (h->count[0] == n)               
        return 0;                       

    
    left = 1;                           
    for (len = 1; len <= MAXBITS; len++) {
        left <<= 1;                     
        left -= h->count[len];          
        if (left < 0) return left;      
    }                                   

    
    offs[1] = 0;
    for (len = 1; len < MAXBITS; len++)
        offs[len + 1] = offs[len] + h->count[len];

    
    for (symbol = 0; symbol < n; symbol++)
        if (length[symbol] != 0)
            h->symbol[offs[length[symbol]]++] = symbol;

    
    return left;
}