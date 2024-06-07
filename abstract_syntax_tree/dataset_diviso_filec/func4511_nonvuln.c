WORD_LIST *
expand_words_no_vars (list)
     WORD_LIST *list;
{
  return (expand_word_list_internal (list, WEXP_NOVARS));