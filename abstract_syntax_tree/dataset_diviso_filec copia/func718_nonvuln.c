static void upnp_event_prepare(struct upnp_event_notify * obj)
{
	static const char notifymsg[] =
		"STR"
		"STR"
#if (UPNP_VERSION_MAJOR == 1) && (UPNP_VERSION_MINOR == 0)
		"STR"	
#else
		"STR"	
#endif
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR";
	char * xml;
	int l;
	if(obj->sub == NULL) {
		obj->state = EError;
		return;
	}
	switch(obj->sub->service) {
	case EWanCFG:
		xml = getVarsWANCfg(&l);
		break;
	case EWanIPC:
		xml = getVarsWANIPCn(&l);
		break;
#ifdef ENABLE_L3F_SERVICE
	case EL3F:
		xml = getVarsL3F(&l);
		break;
#endif
#ifdef ENABLE_6FC_SERVICE
	case E6FC:
		xml = getVars6FC(&l);
		break;
#endif
#ifdef ENABLE_DP_SERVICE
	case EDP:
		xml = getVarsDP(&l);
		break;
#endif
	default:
		xml = NULL;
		l = 0;
	}
	obj->buffersize = 1024;
	for (;;) {
		obj->buffer = malloc(obj->buffersize);
		if(!obj->buffer) {
			syslog(LOG_ERR, "STR");
			if(xml) {
				free(xml);
			}
			obj->state = EError;
			return;
		}
		obj->tosend = snprintf(obj->buffer, obj->buffersize, notifymsg,
		                       obj->path, obj->addrstr, obj->portstr, l+2,
		                       obj->sub->uuid, obj->sub->seq,
		                       l, xml);
		if (obj->tosend < 0) {
			syslog(LOG_ERR, "STR");
			if(xml) {
				free(xml);
			}
			obj->state = EError;
			return;
		} else if (obj->tosend < obj->buffersize) {
			break; 
		}
		
		free(obj->buffer);
		obj->buffersize = obj->tosend + 1;	
	}
	if(xml) {
		free(xml);
		xml = NULL;
	}
	obj->state = ESending;
}