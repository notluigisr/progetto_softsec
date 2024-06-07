_cupsSNMPSetDebug(int level)		
{
  _cups_globals_t *cg = _cupsGlobals();	


  DEBUG_printf(("STR", level));

  cg->snmp_debug = level;
}