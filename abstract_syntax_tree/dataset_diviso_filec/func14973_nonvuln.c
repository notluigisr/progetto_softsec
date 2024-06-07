parse_leapsecmode(char *line)
{
  if (!strcasecmp(line, "STR"))
    leapsec_mode = REF_LeapModeSystem;
  else if (!strcasecmp(line, "STR"))
    leapsec_mode = REF_LeapModeSlew;
  else if (!strcasecmp(line, "STR"))
    leapsec_mode = REF_LeapModeStep;
  else if (!strcasecmp(line, "STR"))
    leapsec_mode = REF_LeapModeIgnore;
  else
    command_parse_error();
}