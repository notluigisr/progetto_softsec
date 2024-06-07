		void CWebServer::Cmd_DeletePlanDevice(WebEmSession & session, const request& req, Json::Value &root)
		{
			if (session.rights != 2)
			{
				session.reply_status = reply::forbidden;
				return; 
			}
			std::string idx = request::findValue(&req, "STR");
			if (idx.empty())
				return;
			root["STR";
			root["STR";
			m_sql.safe_query("STR", idx.c_str());
		}