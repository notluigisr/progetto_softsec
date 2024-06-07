resolve_when_ctx_snode(const struct lys_node *schema, struct lys_node **ctx_snode, enum lyxp_node_type *ctx_snode_type)
{
    const struct lys_node *sparent;

    
    *ctx_snode_type = LYXP_NODE_ELEM;
    while (schema->nodetype & (LYS_USES | LYS_CHOICE | LYS_CASE | LYS_AUGMENT | LYS_INPUT | LYS_OUTPUT)) {
        if (schema->nodetype == LYS_AUGMENT) {
            sparent = ((struct lys_node_augment *)schema)->target;
        } else {
            sparent = schema->parent;
        }
        if (!sparent) {
            
            if (schema->flags & LYS_CONFIG_W) {
                *ctx_snode_type = LYXP_NODE_ROOT_CONFIG;
            } else {
                *ctx_snode_type = LYXP_NODE_ROOT;
            }
            
            schema = lys_getnext(NULL, NULL, lys_node_module(schema), LYS_GETNEXT_NOSTATECHECK);
            break;
        }
        schema = sparent;
    }

    *ctx_snode = (struct lys_node *)schema;
}