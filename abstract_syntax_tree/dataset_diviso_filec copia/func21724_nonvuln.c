static int poll_drive(bool interruptible, int flag)
{
	
	raw_cmd = &default_raw_cmd;
	raw_cmd->flags = flag;
	raw_cmd->track = 0;
	raw_cmd->cmd_count = 0;
	cont = &poll_cont;
	debug_dcl(DP->flags, "STR");
	set_bit(FD_DISK_NEWCHANGE_BIT, &DRS->flags);

	return wait_til_done(floppy_ready, interruptible);
}