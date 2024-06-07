void blk_dump_rq_flags(struct request *rq, char *msg)
{
	printk(KERN_INFO "STR", msg,
		rq->rq_disk ? rq->rq_disk->disk_name : "STR",
		(unsigned long long) rq->cmd_flags);

	printk(KERN_INFO "STR",
	       (unsigned long long)blk_rq_pos(rq),
	       blk_rq_sectors(rq), blk_rq_cur_sectors(rq));
	printk(KERN_INFO "STR",
	       rq->bio, rq->biotail, blk_rq_bytes(rq));
}