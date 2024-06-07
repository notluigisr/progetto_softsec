HotStandbyActiveInReplay(void)
{
	Assert(AmStartupProcess());
	return LocalHotStandbyActive;
}