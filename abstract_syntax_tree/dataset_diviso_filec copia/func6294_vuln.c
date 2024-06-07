runMainLoop(WorkingObjects &wo) {
	ev::io feedbackFdWatcher(eventLoop);
	ev::sig sigintWatcher(eventLoop);
	ev::sig sigtermWatcher(eventLoop);
	ev::sig sigquitWatcher(eventLoop);
	
	if (feedbackFdAvailable()) {
		feedbackFdWatcher.set<&feedbackFdBecameReadable>();
		feedbackFdWatcher.start(FEEDBACK_FD, ev::READ);
		writeArrayMessage(FEEDBACK_FD, "STR", NULL);
	}
	sigintWatcher.set<&caughtExitSignal>();
	sigintWatcher.start(SIGINT);
	sigtermWatcher.set<&caughtExitSignal>();
	sigtermWatcher.start(SIGTERM);
	sigquitWatcher.set<&printInfo>();
	sigquitWatcher.start(SIGQUIT);
	
	P_WARN("STR" << socketAddress);
	ev_run(eventLoop, 0);
}