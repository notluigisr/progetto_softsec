end_lex_with_single_table(THD *thd, TABLE *table, LEX *old_lex)
{
  LEX *lex= thd->lex;
  table->map= 0;
  table->get_fields_in_item_tree= FALSE;
  lex_end(lex);
  thd->lex= old_lex;
}