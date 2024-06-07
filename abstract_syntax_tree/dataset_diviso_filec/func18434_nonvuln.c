void _mi_report_crashed(MI_INFO *file, const char *message,
                        const char *sfile, uint sline)
{
  THD *cur_thd;
  LIST *element;
  char buf[1024];
  mysql_mutex_lock(&file->s->intern_lock);
  if ((cur_thd= (THD*) file->in_use.data))
    sql_print_error("STR", cur_thd->thread_id,
                    sfile, sline);
  else
    sql_print_error("STR", sfile, sline);
  if (message)
    sql_print_error("STR", message);
  for (element= file->s->in_use; element; element= list_rest(element))
  {
    THD *thd= (THD*) element->data;
    sql_print_error("STR", thd ? thd_security_context(thd, buf, sizeof(buf), 0)
                              : "STR");
  }
  mysql_mutex_unlock(&file->s->intern_lock);
}