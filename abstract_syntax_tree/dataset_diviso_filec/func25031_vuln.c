	FileDescriptor connectToHelperAgent() {
		TRACE_POINT();
		FileDescriptor conn;
		
		try {
			conn = connectToUnixServer(agentsStarter.getRequestSocketFilename());
			writeExact(conn, agentsStarter.getRequestSocketPassword());
		} catch (const SystemException &e) {
			if (e.code() == EPIPE || e.code() == ECONNREFUSED || e.code() == ENOENT) {
				UPDATE_TRACE_POINT();
				bool connected = false;
				
				
				usleep(50000);
				
				
				
				time_t deadline = time(NULL) + 5;
				while (!connected && time(NULL) < deadline) {
					try {
						conn = connectToUnixServer(agentsStarter.getRequestSocketFilename());
						writeExact(conn, agentsStarter.getRequestSocketPassword());
						connected = true;
					} catch (const SystemException &e) {
						if (e.code() == EPIPE || e.code() == ECONNREFUSED || e.code() == ENOENT) {
							
							
							usleep(20000 + rand() % 80000);
							
						} else {
							throw;
						}
					}
				}
				
				if (!connected) {
					UPDATE_TRACE_POINT();
					throw IOException("STR");
				}
			} else {
				throw;
			}
		}
		return conn;
	}