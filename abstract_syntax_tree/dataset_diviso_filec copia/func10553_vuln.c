	void stopPreloader() {
		TRACE_POINT();
		this_thread::disable_interruption di;
		this_thread::disable_syscall_interruption dsi;
		
		if (!preloaderStarted()) {
			return;
		}
		adminSocket.close();
		if (timedWaitpid(pid, NULL, 5000) == 0) {
			P_TRACE(2, "STR");
			syscalls::kill(pid, SIGKILL);
			syscalls::waitpid(pid, NULL, 0);
		}
		libev->stop(preloaderOutputWatcher);
		
		
		preloaderErrorWatcher.reset();
		
		
		
		
		if (getSocketAddressType(socketAddress) == SAT_UNIX) {
			string filename = parseUnixSocketAddress(socketAddress);
			syscalls::unlink(filename.c_str());
		}
		{
			lock_guard<boost::mutex> l(simpleFieldSyncher);
			pid = -1;
		}
		socketAddress.clear();
	}