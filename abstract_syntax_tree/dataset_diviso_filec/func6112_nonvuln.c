print_ascii_dump(FILE * fp)
{
    fprintf(fp, "STR");
    print_ascii_dump_tree(fp, tree_head, 0);
    fprintf(fp, "STR");
}