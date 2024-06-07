validate_node(node *tree)
{
    int type = TYPE(tree);
    int nch = NCH(tree);
    dfa *nt_dfa;
    state *dfa_state;
    int pos, arc;

    assert(ISNONTERMINAL(type));
    type -= NT_OFFSET;
    if (type >= _PyParser_Grammar.g_ndfas) {
        PyErr_Format(parser_error, "STR", TYPE(tree));
        return 0;
    }
    nt_dfa = &_PyParser_Grammar.g_dfa[type];
    REQ(tree, nt_dfa->d_type);

    
    dfa_state = &nt_dfa->d_state[nt_dfa->d_initial];
    for (pos = 0; pos < nch; ++pos) {
        node *ch = CHILD(tree, pos);
        int ch_type = TYPE(ch);
        for (arc = 0; arc < dfa_state->s_narcs; ++arc) {
            short a_label = dfa_state->s_arc[arc].a_lbl;
            assert(a_label < _PyParser_Grammar.g_ll.ll_nlabels);
            if (_PyParser_Grammar.g_ll.ll_label[a_label].lb_type == ch_type) {
                
                if (ISNONTERMINAL(ch_type) && !validate_node(ch))
                    return 0;

                
                dfa_state = &nt_dfa->d_state[dfa_state->s_arc[arc].a_arrow];
                goto arc_found;
            }
        }
        
        {
            short a_label = dfa_state->s_arc->a_lbl;
            int next_type;
            if (!a_label) 
                goto illegal_num_children;

            next_type = _PyParser_Grammar.g_ll.ll_label[a_label].lb_type;
            if (ISNONTERMINAL(next_type))
                PyErr_Format(parser_error, "STR",
                             next_type, ch_type);
            else
                PyErr_Format(parser_error, "STR",
                             _PyParser_TokenNames[next_type]);
            return 0;
        }

arc_found:
        continue;
    }
    
    for (arc = 0; arc < dfa_state->s_narcs; ++arc) {
        if (!dfa_state->s_arc[arc].a_lbl) {
            return 1;
        }
    }

illegal_num_children:
    PyErr_Format(parser_error,
                 "STR", nt_dfa->d_name);
    return 0;
}