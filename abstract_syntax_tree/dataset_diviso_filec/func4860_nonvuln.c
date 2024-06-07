lyd_insert_after(struct lyd_node *sibling, struct lyd_node *node)
{
    if (!node || !sibling) {
        LOGARG;
        return EXIT_FAILURE;
    }

    return lyd_insert_nextto(sibling, node, 0, 1);
}