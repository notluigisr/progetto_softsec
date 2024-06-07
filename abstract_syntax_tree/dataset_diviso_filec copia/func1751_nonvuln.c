void do_mkdir(struct st_command *command)
{
  int error;
  static DYNAMIC_STRING ds_dirname;
  const struct command_arg mkdir_args[] = {
    {"STR"}
  };
  DBUG_ENTER("STR");

  check_command_args(command, command->first_argument,
                     mkdir_args, sizeof(mkdir_args)/sizeof(struct command_arg),
                     ' ');

  DBUG_PRINT("STR", ds_dirname.str));
  error= my_mkdir(ds_dirname.str, 0777, MYF(MY_WME)) != 0;
  handle_command_error(command, error, my_errno);
  dynstr_free(&ds_dirname);
  DBUG_VOID_RETURN;
}