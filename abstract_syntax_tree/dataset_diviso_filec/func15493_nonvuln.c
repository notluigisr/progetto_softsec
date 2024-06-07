		void CWebServer::Cmd_ClearShortLog(WebEmSession & session, const request& req, Json::Value &root)
		{
			if (session.rights != 2)
			{
				session.reply_status = reply::forbidden;
				return; 
			}
			root["STR";
			root["STR";

			_log.Log(LOG_STATUS, "STR");

			m_sql.ClearShortLog();

			_log.Log(LOG_STATUS, "STR");
		}