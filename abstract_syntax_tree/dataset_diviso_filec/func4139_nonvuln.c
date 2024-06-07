local int build_bl_tree(s)
    deflate_state *s;
{
    int max_blindex;  

    
    scan_tree(s, (ct_data *)s->dyn_ltree, s->l_desc.max_code);
    scan_tree(s, (ct_data *)s->dyn_dtree, s->d_desc.max_code);

    
    build_tree(s, (tree_desc *)(&(s->bl_desc)));
    

    
    for (max_blindex = BL_CODES-1; max_blindex >= 3; max_blindex--) {
        if (s->bl_tree[bl_order[max_blindex]].Len != 0) break;
    }
    
    s->opt_len += 3*((ulg)max_blindex+1) + 5+5+4;
    Tracev((stderr, "STR",
            s->opt_len, s->static_len));

    return max_blindex;
}