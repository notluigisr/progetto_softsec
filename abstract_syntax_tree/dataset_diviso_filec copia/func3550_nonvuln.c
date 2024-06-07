free_node(struct node *np)
{
    if (!np)
        return;

    free_enums(&np->enums);
    free_ranges(&np->ranges);
    free_indexes(&np->indexes);
    free_varbinds(&np->varbinds);
    if (np->label)
        free(np->label);
    if (np->hint)
        free(np->hint);
    if (np->units)
        free(np->units);
    if (np->description)
        free(np->description);
    if (np->reference)
        free(np->reference);
    if (np->defaultValue)
        free(np->defaultValue);
    if (np->parent)
        free(np->parent);
    if (np->augments)
        free(np->augments);
    if (np->filename)
	free(np->filename);
    free((char *) np);
}