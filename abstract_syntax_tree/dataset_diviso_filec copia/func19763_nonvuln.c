static int auth_init(void) {
   
  pr_help_add(C_USER, _("STR"), TRUE);
  pr_help_add(C_PASS, _("STR"), TRUE);
  pr_help_add(C_ACCT, _("STR"), FALSE);
  pr_help_add(C_REIN, _("STR"), FALSE);

  
  set_auth_check(auth_cmd_chk_cb);

  return 0;
}