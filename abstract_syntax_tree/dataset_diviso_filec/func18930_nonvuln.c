int ha_myisam::repair(THD* thd, HA_CHECK_OPT *check_opt)
{
  int error;
  MI_CHECK param;
  ha_rows start_records;

  if (!file) return HA_ADMIN_INTERNAL_ERROR;

  myisamchk_init(&param);
  param.thd = thd;
  param.op_name=  "STR";
  param.testflag= ((check_opt->flags & ~(T_EXTEND)) |
                   T_SILENT | T_FORCE_CREATE | T_CALC_CHECKSUM |
                   (check_opt->flags & T_EXTEND ? T_REP : T_REP_BY_SORT));
  param.sort_buffer_length=  THDVAR(thd, sort_buffer_size);
  start_records=file->state->records;
  while ((error=repair(thd,param,0)) && param.retry_repair)
  {
    param.retry_repair=0;
    if (test_all_bits(param.testflag,
		      (uint) (T_RETRY_WITHOUT_QUICK | T_QUICK)))
    {
      param.testflag&= ~T_RETRY_WITHOUT_QUICK;
      sql_print_information("STR",
                            table->s->path.str);
      continue;
    }
    param.testflag&= ~T_QUICK;
    if ((param.testflag & T_REP_BY_SORT))
    {
      param.testflag= (param.testflag & ~T_REP_BY_SORT) | T_REP;
      sql_print_information("STR",
                            table->s->path.str);
      continue;
    }
    break;
  }
  if (!error && start_records != file->state->records &&
      !(check_opt->flags & T_VERY_SILENT))
  {
    char llbuff[22],llbuff2[22];
    sql_print_information("STR",
                          llstr(file->state->records, llbuff),
                          llstr(start_records, llbuff2),
                          table->s->path.str);
  }
  return error;
}