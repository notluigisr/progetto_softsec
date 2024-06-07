static void sas_eh_finish_cmd(struct scsi_cmnd *cmd)
{
	struct sas_ha_struct *sas_ha = SHOST_TO_SAS_HA(cmd->device->host);
	struct sas_task *task = TO_SAS_TASK(cmd);

	
	sas_end_task(cmd, task);

	
	scsi_eh_finish_cmd(cmd, &sas_ha->eh_done_q);
}