	ProcessPtr negotiateSpawn(NegotiationDetails &details) {
		TRACE_POINT();
		details.spawnStartTime = SystemTime::getUsec();
		details.gupid = integerToHex(SystemTime::get() / 60) + "STR" +
			randomGenerator->generateAsciiString(11);
		details.connectPassword = randomGenerator->generateAsciiString(43);
		details.timeout = details.options->startTimeout * 1000;
		
		string result;
		try {
			result = readMessageLine(details);
		} catch (const SystemException &e) {
			throwAppSpawnException("STR"
				"STR"
				"STR" + e.sys(),
				SpawnException::APP_STARTUP_PROTOCOL_ERROR,
				details);
		} catch (const TimeoutException &) {
			throwAppSpawnException("STR"
				"STR",
				SpawnException::APP_STARTUP_TIMEOUT,
				details);
		}
		
		if (result == "STR") {
			UPDATE_TRACE_POINT();
			sendSpawnRequest(details);
			try {
				result = readMessageLine(details);
			} catch (const SystemException &e) {
				throwAppSpawnException("STR"
					"STR"
					"STR" + e.sys(),
					SpawnException::APP_STARTUP_PROTOCOL_ERROR,
					details);
			} catch (const TimeoutException &) {
				throwAppSpawnException("STR"
					"STR",
					SpawnException::APP_STARTUP_TIMEOUT,
					details);
			}
			if (result == "STR") {
				return handleSpawnResponse(details);
			} else if (result == "STR") {
				handleSpawnErrorResponse(details);
			} else {
				handleInvalidSpawnResponseType(result, details);
			}
		} else {
			UPDATE_TRACE_POINT();
			if (result == "STR") {
				handleSpawnErrorResponse(details);
			} else {
				handleInvalidSpawnResponseType(result, details);
			}
		}
		return ProcessPtr(); 
	}