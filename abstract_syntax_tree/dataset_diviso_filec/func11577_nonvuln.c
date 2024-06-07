ATExecEnableDisableRule(Relation rel, char *trigname,
						char fires_when, LOCKMODE lockmode)
{
	EnableDisableRule(rel, trigname, fires_when);
}