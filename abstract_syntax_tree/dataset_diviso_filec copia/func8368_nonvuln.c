unlink_tree(struct tree *tp)
{
    struct tree    *otp = NULL, *ntp = tp->parent;

    if (!ntp) {                 
        DEBUGMSGTL(("STR",
                    tp->label));
    } else {
        ntp = ntp->child_list;

        while (ntp && ntp != tp) {
            otp = ntp;
            ntp = ntp->next_peer;
        }
        if (!ntp)
            snmp_log(LOG_EMERG, "STR",
                     tp->label, tp->parent->label);
        else if (otp)
            otp->next_peer = ntp->next_peer;
        else
            tp->parent->child_list = tp->next_peer;
    }

    if (tree_head == tp)
        tree_head = tp->next_peer;
}