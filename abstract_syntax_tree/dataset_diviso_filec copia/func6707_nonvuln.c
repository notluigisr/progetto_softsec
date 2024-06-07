static void uas_log_cmd_state(struct scsi_cmnd *cmnd, const char *prefix,
			      int status)
{
	struct uas_cmd_info *ci = (void *)&cmnd->SCp;
	struct uas_cmd_info *cmdinfo = (void *)&cmnd->SCp;

	scmd_printk(KERN_INFO, cmnd,
		    "STR",
		    prefix, status, cmdinfo->uas_tag,
		    (ci->state & SUBMIT_STATUS_URB)     ? "STR",
		    (ci->state & ALLOC_DATA_IN_URB)     ? "STR",
		    (ci->state & SUBMIT_DATA_IN_URB)    ? "STR",
		    (ci->state & ALLOC_DATA_OUT_URB)    ? "STR",
		    (ci->state & SUBMIT_DATA_OUT_URB)   ? "STR",
		    (ci->state & ALLOC_CMD_URB)         ? "STR",
		    (ci->state & SUBMIT_CMD_URB)        ? "STR",
		    (ci->state & COMMAND_INFLIGHT)      ? "STR",
		    (ci->state & DATA_IN_URB_INFLIGHT)  ? "STR",
		    (ci->state & DATA_OUT_URB_INFLIGHT) ? "STR",
		    (ci->state & COMMAND_ABORTED)       ? "STR",
		    (ci->state & IS_IN_WORK_LIST)       ? "STR");
	scsi_print_command(cmnd);
}