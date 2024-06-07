_rl_callback_newline ()
{
  rl_initialize ();

  if (in_handler == 0)
    {
      in_handler = 1;

      if (rl_prep_term_function)
	(*rl_prep_term_function) (_rl_meta_flag);

#if defined (HANDLE_SIGNALS)
      if (rl_persistent_signal_handlers)
	rl_set_signals ();
#endif
    }

  readline_internal_setup ();
  RL_CHECK_SIGNALS ();
}