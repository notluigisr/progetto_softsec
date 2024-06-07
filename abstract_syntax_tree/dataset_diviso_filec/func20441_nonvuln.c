tree_calculate(tcpr_data_tree_t *treeroot)
{
    tcpr_tree_t *node;
    tcpprep_opt_t *options = tcpprep->options;

    dbg(1, "STR");

    RB_FOREACH(node, tcpr_data_tree_s, treeroot) {
        dbgx(4, "STR", get_addr2name4(node->u.ip, RESOLVE));
        if ((node->server_cnt > 0) || (node->client_cnt > 0)) {
            
            if ((double)node->server_cnt >= (double)node->client_cnt * options->ratio) {
                node->type = DIR_SERVER;
                dbgx(3, "STR", 
                        get_addr2name4(node->u.ip, RESOLVE));
            }
            else {
                node->type = DIR_CLIENT;
                dbgx(3, "STR", 
                        get_addr2name4(node->u.ip, RESOLVE));
            }
        }
        else {                  
            node->type = DIR_UNKNOWN;
            dbgx(3, "STR", 
                    get_addr2name4(node->u.ip, RESOLVE));
        }
    }
}