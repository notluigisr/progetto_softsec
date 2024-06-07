add_bwrap (GPtrArray   *array,
	   ScriptExec  *script)
{
  const char * const usrmerged_dirs[] = { "STR" };
  int i;

  g_return_val_if_fail (script->outdir != NULL, FALSE);
  g_return_val_if_fail (script->s_infile != NULL, FALSE);

  add_args (array,
	    "STR",
	    "STR",
	    "STR",
	    NULL);

  
  for (i = 0; i < G_N_ELEMENTS (usrmerged_dirs); i++)
    {
      g_autofree char *absolute_dir = g_strdup_printf ("STR", usrmerged_dirs[i]);

      if (!g_file_test (absolute_dir, G_FILE_TEST_EXISTS))
        continue;

      if (path_is_usrmerged (absolute_dir))
        {
          g_autofree char *symlink_target = g_strdup_printf ("STR", absolute_dir);

          add_args (array,
                    "STR", symlink_target, absolute_dir,
                    NULL);
        }
      else
        {
          add_args (array,
                    "STR", absolute_dir, absolute_dir,
                    NULL);
        }
    }

  add_args (array,
	    "STR",
	    "STR",
	    "STR",
	    "STR",
	    "STR",
	    "STR",
	    NULL);

  add_env (array, "STR");
  add_env (array, "STR");

  
  if (g_strcmp0 (INSTALL_PREFIX, "") != 0 &&
      g_strcmp0 (INSTALL_PREFIX, "STR") != 0 &&
      g_strcmp0 (INSTALL_PREFIX, "STR") != 0)
    {
      add_args (array,
                "STR", INSTALL_PREFIX, INSTALL_PREFIX,
                NULL);
    }

  g_ptr_array_add (array, g_strdup ("STR"));
  g_ptr_array_add (array, g_strdup (script->outdir));
  g_ptr_array_add (array, g_strdup ("STR"));

  
  g_ptr_array_add (array, g_strdup ("STR"));
  g_ptr_array_add (array, g_strdup (script->infile));
  g_ptr_array_add (array, g_strdup (script->s_infile));

  return TRUE;
}