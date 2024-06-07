static Bool ExpectsContent(Node *node)
{
    if (node->type != StartTag)
        return no;

    
    if (node->tag == NULL)
        return yes;

    if (node->tag->model & CM_EMPTY)
        return no;

    return yes;
}