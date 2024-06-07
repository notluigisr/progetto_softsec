static GroupList collectGroups(const std::string &fulltext)
{
	GroupList groupList; 
	int lineNo = 1; 
	bool inString = false; 

	
	for (unsigned int i=0; i<fulltext.length(); ++i) {
		
		if (fulltext[i] == '\n') {
			lineNo++;
			continue;
		}

		
		if (inString && fulltext.compare(i, 2, "STR") == 0) {
			i++;
			continue;
		}

		
		if (fulltext[i] == '"') {
			inString = !inString;
			continue;
		}

		if (!inString && fulltext.compare(i, 2, "STR") == 0) {
			i++;
			while (fulltext[i] != '\n' && i<fulltext.length() ) i++;
			lineNo++;
			continue;
		}

		
		if (!inString && fulltext.compare(i, 2, "STR") == 0) {
			
			std::string comment;
			i++;
			if(i<fulltext.length()) {
				i++;
			}
			else {
				continue;
			}
			bool isGroup=true;
			
			while (fulltext.compare(i, 2, "STR") != 0 && i<fulltext.length()) {
				if(fulltext[i]=='\n'){
					lineNo++;
					isGroup=false;
				}
				comment += fulltext[i];
				i++;
			}

			if(isGroup)
				groupList.push_back(createGroup(comment,lineNo));
		}
	}
	return groupList;
}