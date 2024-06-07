static int date_from_ISO8601 (const char *text, time_t * value) {
   struct tm tm;
   int n;
   int i;
	char buf[18];

	if (strchr (text, '-')) {
		char *p = (char *) text, *p2 = buf;
		while (p && *p) {
			if (*p != '-') {
				*p2 = *p;
				p2++;
			}
			p++;
		}
			text = buf;
	}


   tm.tm_isdst = -1;

   if(strlen(text) < 17) {
      return -1;
   }



   n = 1000;
   tm.tm_year = 0;
   for(i = 0; i < 4; i++) {
      XMLRPC_IS_NUMBER(text[i])
      tm.tm_year += (text[i]-'0')*n;
      n /= 10;
   }
   n = 10;
   tm.tm_mon = 0;
   for(i = 0; i < 2; i++) {
      XMLRPC_IS_NUMBER(text[i])
      tm.tm_mon += (text[i+4]-'0')*n;
      n /= 10;
   }
   tm.tm_mon --;

   n = 10;
   tm.tm_mday = 0;
   for(i = 0; i < 2; i++) {
      XMLRPC_IS_NUMBER(text[i])
      tm.tm_mday += (text[i+6]-'0')*n;
      n /= 10;
   }

   n = 10;
   tm.tm_hour = 0;
   for(i = 0; i < 2; i++) {
      XMLRPC_IS_NUMBER(text[i])
      tm.tm_hour += (text[i+9]-'0')*n;
      n /= 10;
   }

   n = 10;
   tm.tm_min = 0;
   for(i = 0; i < 2; i++) {
      XMLRPC_IS_NUMBER(text[i])
      tm.tm_min += (text[i+12]-'0')*n;
      n /= 10;
   }

   n = 10;
   tm.tm_sec = 0;
   for(i = 0; i < 2; i++) {
      XMLRPC_IS_NUMBER(text[i])
      tm.tm_sec += (text[i+15]-'0')*n;
      n /= 10;
   }

   tm.tm_year -= 1900;

   *value = mktime(&tm);

   return 0;

}