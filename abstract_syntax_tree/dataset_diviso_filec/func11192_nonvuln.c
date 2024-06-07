lys_is_disabled(const struct lys_node *node, int recursive)
{
    int i;

    if (!node) {
        return NULL;
    }

check:
    if (node->nodetype != LYS_INPUT && node->nodetype != LYS_OUTPUT) {
        

        
        for (i = 0; i < node->iffeature_size; i++) {
            if (!resolve_iffeature(&node->iffeature[i])) {
                return node;
            }
        }
    }

    if (!recursive) {
        return NULL;
    }

    
    if (node->nodetype == LYS_AUGMENT) {
        
        node = ((struct lys_node_augment *)node)->target;
        if (!node) {
            
            return NULL;
        }
    } else if (node->nodetype == LYS_EXT) {
        return NULL;
    } else if (node->parent) {
        node = node->parent;
    } else {
        return NULL;
    }

    if (recursive == 2) {
        
        if (node->nodetype & (LYS_CONTAINER | LYS_LEAF | LYS_LEAFLIST | LYS_LIST)) {
            return NULL;
        }
    }
    goto check;
}