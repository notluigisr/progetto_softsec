SDL_ListRemove(SDL_ListNode **head, void *ent)
{
    SDL_ListNode **ptr = head;

    while (*ptr) {
        if ((*ptr)->entry == ent) {
            SDL_ListNode *tmp = *ptr;
            *ptr = (*ptr)->next;
            SDL_free(tmp);
            return;
        }
        ptr = &(*ptr)->next;
    }
}