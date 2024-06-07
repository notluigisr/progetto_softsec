ipvs_syncd_master(const struct lvs_syncd_config *config)
{
	ipvs_syncd_cmd(IPVS_STOPDAEMON, config, IPVS_BACKUP, false, false);
	ipvs_syncd_cmd(IPVS_STARTDAEMON, config, IPVS_MASTER, false, false);
}