init_switches (void)
{
  char *p = short_options;
  size_t i, o = 0;
  for (i = 0; i < countof (option_data); i++)
    {
      struct cmdline_option *cmdopt = &option_data[i];
      struct option *longopt;

      if (!cmdopt->long_name)
        
        continue;

      longopt = &long_options[o++];
      longopt->name = cmdopt->long_name;
      longopt->val = i;
      if (cmdopt->short_name)
        {
          *p++ = cmdopt->short_name;
          optmap[cmdopt->short_name - 32] = longopt - long_options;
        }
      switch (cmdopt->type)
        {
        case OPT_VALUE:
          longopt->has_arg = required_argument;
          if (cmdopt->short_name)
            *p++ = ':';
          break;
        case OPT_BOOLEAN:
          
          longopt->has_arg = optional_argument;
          
          longopt = &long_options[o++];
          longopt->name = no_prefix (cmdopt->long_name);
          longopt->has_arg = no_argument;
          
          longopt->val = i | BOOLEAN_NEG_MARKER;
          break;
        default:
          assert (cmdopt->argtype != -1);
          longopt->has_arg = cmdopt->argtype;
          if (cmdopt->short_name)
            {
              if (longopt->has_arg == required_argument)
                *p++ = ':';
              
            }
        }
    }
  
  *p = '\0';
  
  assert (o <= countof (long_options));
}