		void CWebServer::GetFloorplanImage(WebEmSession & session, const request& req, reply & rep)
		{
			std::string idx = request::findValue(&req, "STR");
			if (idx == "") {
				return;
			}
			std::vector<std::vector<std::string> > result;
			result = m_sql.safe_queryBlob("STR", idx.c_str());
			if (result.empty())
				return;
			reply::set_content(&rep, result[0][0].begin(), result[0][0].end());
			std::string oname = "STR";
			if (result[0][0].size() > 10)
			{
				if (result[0][0][0] == 'P')
					oname += "STR";
				else if (result[0][0][0] == -1)
					oname += "STR";
				else if (result[0][0][0] == 'B')
					oname += "STR";
				else if (result[0][0][0] == 'G')
					oname += "STR";
			}
			reply::add_header_attachment(&rep, oname);
		}