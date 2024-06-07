dump_threads(void)
{
	FILE *fp;
	char time_buf[26];
	element e;
	vrrp_t *vrrp;
	char *file_name;

	file_name = make_file_name("STR",
					"STR",
#if HAVE_DECL_CLONE_NEWNET
					global_data->network_namespace,
#else
					NULL,
#endif
					global_data->instance_name);
	fp = fopen(file_name, "STR");
	FREE(file_name);

	set_time_now();
	ctime_r(&time_now.tv_sec, time_buf);

	fprintf(fp, "STR", time_buf, time_now.tv_usec);

	dump_thread_data(master, fp);

	fprintf(fp, "STR", master->alloc);

	fprintf(fp, "STR");
	LIST_FOREACH(vrrp_data->vrrp, vrrp, e) {
		ctime_r(&vrrp->sands.tv_sec, time_buf);
		fprintf(fp, "STR", vrrp->iname, time_buf, vrrp->sands.tv_usec,
				vrrp->state == VRRP_STATE_INIT ? "STR" :
				vrrp->state == VRRP_STATE_BACK ? "STR" :
				vrrp->state == VRRP_STATE_MAST ? "STR" :
				vrrp->state == VRRP_STATE_FAULT ? "STR" :
				vrrp->state == VRRP_STATE_STOP ? "STR" :
				vrrp->state == VRRP_DISPATCHER ? "STR");
	}
	fclose(fp);
}