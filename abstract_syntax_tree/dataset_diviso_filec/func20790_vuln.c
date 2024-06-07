local int fixed(struct state *s)
{
    static int virgin = 1;
    static boost::int16_t lencnt[MAXBITS+1], lensym[FIXLCODES];
    static boost::int16_t distcnt[MAXBITS+1], distsym[MAXDCODES];
    static struct huffman lencode = {lencnt, lensym};
    static struct huffman distcode = {distcnt, distsym};

    
    if (virgin) {
        int symbol;
        boost::int16_t lengths[FIXLCODES];

        
        for (symbol = 0; symbol < 144; symbol++)
            lengths[symbol] = 8;
        for (; symbol < 256; symbol++)
            lengths[symbol] = 9;
        for (; symbol < 280; symbol++)
            lengths[symbol] = 7;
        for (; symbol < FIXLCODES; symbol++)
            lengths[symbol] = 8;
        construct(&lencode, lengths, FIXLCODES);

        
        for (symbol = 0; symbol < MAXDCODES; symbol++)
            lengths[symbol] = 5;
        construct(&distcode, lengths, MAXDCODES);

        
        virgin = 0;
    }

    
    return codes(s, &lencode, &distcode);
}