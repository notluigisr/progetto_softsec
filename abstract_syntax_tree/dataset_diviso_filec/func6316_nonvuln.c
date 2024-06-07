window_pane_destroy(struct window_pane *wp)
{
	window_pane_reset_mode(wp);
	free(wp->searchstr);

	if (wp->fd != -1) {
		bufferevent_free(wp->event);
		close(wp->fd);
	}

	input_free(wp);

	screen_free(&wp->base);
	if (wp->saved_grid != NULL)
		grid_destroy(wp->saved_grid);

	if (wp->pipe_fd != -1) {
		bufferevent_free(wp->pipe_event);
		close(wp->pipe_fd);
	}

	if (event_initialized(&wp->resize_timer))
		event_del(&wp->resize_timer);

	RB_REMOVE(window_pane_tree, &all_window_panes, wp);

	free((void *)wp->cwd);
	free(wp->shell);
	cmd_free_argv(wp->argc, wp->argv);
	free(wp->palette);
	free(wp);
}