		void CWebServer::Cmd_EmailCameraSnapshot(WebEmSession & session, const request& req, Json::Value &root)
		{
			std::string camidx = request::findValue(&req, "STR");
			std::string subject = request::findValue(&req, "STR");
			if (
				(camidx.empty()) ||
				(subject.empty())
				)
				return;
			
			m_sql.AddTaskItem(_tTaskItem::EmailCameraSnapshot(1, camidx, subject));
			root["STR";
			root["STR";
		}