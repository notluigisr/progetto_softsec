void undefer_input(__G)
    __GDEF
{
    if (G.incnt > 0)
        G.csize += G.incnt;
    if (G.incnt_leftover > 0) {
        
        G.incnt = G.incnt_leftover + (int)G.csize;
        G.inptr = G.inptr_leftover - (int)G.csize;
        G.incnt_leftover = 0;
    } else if (G.incnt < 0)
        G.incnt = 0;
} 