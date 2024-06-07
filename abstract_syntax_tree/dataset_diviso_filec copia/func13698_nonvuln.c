NOEXPORT void name_list_append(NAME_LIST **ptr, char *name) {
    while(*ptr) 
        ptr=&(*ptr)->next;
    *ptr=str_alloc_detached(sizeof(NAME_LIST));
    (*ptr)->name=str_dup_detached(name);
    (*ptr)->next=NULL;
}