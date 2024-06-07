lyd_insert_sibling(struct lyd_node **sibling, struct lyd_node *node)
{
    if (!sibling || !node) {
        LOGARG;
        return EXIT_FAILURE;
    }

    return lyd_insert_common((*sibling) ? (*sibling)->parent : NULL, sibling, node, 1);

}