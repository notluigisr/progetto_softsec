static void set_thd_in_use_temporary_tables(Relay_log_info *rli)
{
  TABLE *table;

  for (table= rli->save_temporary_tables ; table ; table= table->next)
  {
    table->in_use= rli->info_thd;
    if (table->file != NULL)
    {
      
      table->file->unbind_psi();
      table->file->rebind_psi();
    }
  }
}