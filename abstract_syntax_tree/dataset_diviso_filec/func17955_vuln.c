local int bits(struct state *s, int need)
{
	boost::int32_t val;           

    
    val = s->bitbuf;
    while (s->bitcnt < need) {
        if (s->incnt == s->inlen) longjmp(s->env, 1);   
        val |= (boost::int32_t)(s->in[s->incnt++]) << s->bitcnt;  
        s->bitcnt += 8;
    }

    
    s->bitbuf = (int)(val >> need);
    s->bitcnt -= need;

    
    return (int)(val & ((1L << need) - 1));
}