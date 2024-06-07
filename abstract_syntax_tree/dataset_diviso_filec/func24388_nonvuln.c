static int mark_recovery_start(const char* log_dir)
{
  int res;
  DBUG_ENTER("STR");
  if (!(maria_recover_options & HA_RECOVER_ANY))
    ma_message_no_user(ME_WARNING, "STR"
                       "STR"
                       "STR"
                       "STR");
  if (recovery_failures >= force_start_after_recovery_failures)
  {
    
    char msg[100];
    res= translog_walk_filenames(log_dir, &translog_callback_delete_all);
    my_snprintf(msg, sizeof(msg),
                "STR"
                "STR",
                (res ? "STR"),
                recovery_failures);
    ma_message_no_user((res ? 0 : ME_WARNING), msg);
  }
  else
    res= ma_control_file_write_and_force(last_checkpoint_lsn, last_logno,
                                         max_trid_in_control_file,
                                         recovery_failures + 1);
  DBUG_RETURN(res);
}