lys_has_xpath(const struct lys_node *node)
{
    assert(node);

    switch (node->nodetype) {
    case LYS_AUGMENT:
        if (((struct lys_node_augment *)node)->when) {
            return 1;
        }
        break;
    case LYS_CASE:
        if (((struct lys_node_case *)node)->when) {
            return 1;
        }
        break;
    case LYS_CHOICE:
        if (((struct lys_node_choice *)node)->when) {
            return 1;
        }
        break;
    case LYS_ANYDATA:
        if (((struct lys_node_anydata *)node)->when || ((struct lys_node_anydata *)node)->must_size) {
            return 1;
        }
        break;
    case LYS_LEAF:
        if (((struct lys_node_leaf *)node)->when || ((struct lys_node_leaf *)node)->must_size) {
            return 1;
        }
        break;
    case LYS_LEAFLIST:
        if (((struct lys_node_leaflist *)node)->when || ((struct lys_node_leaflist *)node)->must_size) {
            return 1;
        }
        break;
    case LYS_LIST:
        if (((struct lys_node_list *)node)->when || ((struct lys_node_list *)node)->must_size) {
            return 1;
        }
        break;
    case LYS_CONTAINER:
        if (((struct lys_node_container *)node)->when || ((struct lys_node_container *)node)->must_size) {
            return 1;
        }
        break;
    case LYS_INPUT:
    case LYS_OUTPUT:
        if (((struct lys_node_inout *)node)->must_size) {
            return 1;
        }
        break;
    case LYS_NOTIF:
        if (((struct lys_node_notif *)node)->must_size) {
            return 1;
        }
        break;
    case LYS_USES:
        if (((struct lys_node_uses *)node)->when) {
            return 1;
        }
        break;
    default:
        
        break;
    }

    return 0;
}