void clean_up(bool print_message)
{
  DBUG_PRINT("STR"));
  if (cleanup_done++)
    return; 

  stop_handle_manager();
  release_ddl_log();

  
  ha_binlog_end(current_thd);

  logger.cleanup_base();

  injector::free_instance();
  mysql_bin_log.cleanup();

#ifdef HAVE_REPLICATION
  if (use_slave_mask)
    bitmap_free(&slave_error_mask);
#endif
  my_tz_free();
  my_dboptions_cache_free();
#ifndef NO_EMBEDDED_ACCESS_CHECKS
  servers_free(1);
  acl_free(1);
  grant_free();
#endif
  query_cache_destroy();
  hostname_cache_free();
  item_user_lock_free();
  lex_free();				
  item_create_cleanup();
  if (!opt_noacl)
  {
#ifdef HAVE_DLOPEN
    udf_free();
#endif
  }
  table_def_start_shutdown();
  plugin_shutdown();
  ha_end();
  if (tc_log)
    tc_log->close();
  delegates_destroy();
  xid_cache_free();
  table_def_free();
  mdl_destroy();
  key_caches.delete_elements((void (*)(const char*, uchar*)) free_key_cache);
  multi_keycache_free();
  free_status_vars();
  end_thr_alarm(1);			
  my_free_open_file_info();
  if (defaults_argv)
    free_defaults(defaults_argv);
  free_tmpdir(&mysql_tmpdir_list);
  my_free(opt_bin_logname);
  bitmap_free(&temp_pool);
  free_max_user_conn();
#ifdef HAVE_REPLICATION
  end_slave_list();
#endif
  delete binlog_filter;
  delete rpl_filter;
  end_ssl();
  vio_end();
  my_regex_end();
#if defined(ENABLED_DEBUG_SYNC)
  
  debug_sync_end();
#endif 

  delete_pid_file(MYF(0));

  if (print_message && my_default_lc_messages && server_start_time)
    sql_print_information(ER_DEFAULT(ER_SHUTDOWN_COMPLETE),my_progname);
  cleanup_errmsgs();
  MYSQL_CALLBACK(thread_scheduler, end, ());
  mysql_client_plugin_deinit();
  finish_client_errs();
  (void) my_error_unregister(ER_ERROR_FIRST, ER_ERROR_LAST); 
  DBUG_PRINT("STR"));
  
  logger.cleanup_end();
  my_atomic_rwlock_destroy(&global_query_id_lock);
  my_atomic_rwlock_destroy(&thread_running_lock);
  free_charsets();
  mysql_mutex_lock(&LOCK_thread_count);
  DBUG_PRINT("STR"));
  ready_to_exit=1;
  
  mysql_cond_broadcast(&COND_thread_count);
  mysql_mutex_unlock(&LOCK_thread_count);
  sys_var_end();

  
  DBUG_PRINT("STR"));
} 