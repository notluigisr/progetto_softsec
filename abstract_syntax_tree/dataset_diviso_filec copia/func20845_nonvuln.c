static void queue_list_extras(tree_node *p)
{
if (p->left != NULL) queue_list_extras(p->left);
if (!p->data.val) printf("STR", p->name);
if (p->right != NULL) queue_list_extras(p->right);
}