R_API void r_core_fini(RCore *c) {
	if (!c) {
		return;
	}
	r_core_task_break_all (&c->tasks);
	r_core_task_join (&c->tasks, NULL, -1);
	r_core_wait (c);
	
	
	
	r_list_free (c->ropchain);
	r_event_free (c->ev);
	free (c->cmdlog);
	free (c->lastsearch);
	R_FREE (c->cons->pager);
	free (c->cmdqueue);
	free (c->lastcmd);
	free (c->stkcmd);
	r_list_free (c->visual.tabs);
	free (c->block);
	r_core_autocomplete_free (c->autocomplete);

	r_list_free (c->gadgets);
	r_list_free (c->undos);
	r_num_free (c->num);
	
	
	
	
	free (c->table_query);
	r_list_free (c->files);
	r_list_free (c->watchers);
	r_list_free (c->scriptstack);
	r_core_task_scheduler_fini (&c->tasks);
	c->rcmd = r_cmd_free (c->rcmd);
	r_list_free (c->cmd_descriptors);
	c->anal = r_anal_free (c->anal);
	r_asm_free (c->assembler);
	c->assembler = NULL;
	c->print = r_print_free (c->print);
	c->bin = (r_bin_free (c->bin), NULL);
	c->lang = (r_lang_free (c->lang), NULL);
	c->dbg = (r_debug_free (c->dbg), NULL);
	r_io_free (c->io);
	r_config_free (c->config);
	
	
	r_cons_free ();
	r_cons_singleton ()->teefile = NULL; 
	r_search_free (c->search);
	r_flag_free (c->flags);
	r_fs_free (c->fs);
	r_egg_free (c->egg);
	r_lib_free (c->lib);
	r_buf_free (c->yank_buf);
	r_agraph_free (c->graph);
	free (c->asmqjmps);
	sdb_free (c->sdb);
	r_core_log_free (c->log);
	r_parse_free (c->parser);
	free (c->times);
}