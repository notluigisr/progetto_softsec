determ_context_t<history_t>::~determ_context_t()
{
    delete[] newprectbl;
    delete[] histlevel;
}