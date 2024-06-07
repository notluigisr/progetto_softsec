const char *get_icalcomponent_errstr(icalcomponent *ical)
{
    icalcomponent *comp;

    for (comp = icalcomponent_get_first_component(ical, ICAL_ANY_COMPONENT);
	 comp;
	 comp = icalcomponent_get_next_component(ical, ICAL_ANY_COMPONENT)) {
	icalproperty *prop;

	for (prop = icalcomponent_get_first_property(comp, ICAL_ANY_PROPERTY);
	     prop;
	     prop = icalcomponent_get_next_property(comp, ICAL_ANY_PROPERTY)) {

	    if (icalproperty_isa(prop) == ICAL_XLICERROR_PROPERTY) {
		icalparameter *param;
		const char *errstr = icalproperty_get_xlicerror(prop);

		if (!errstr) return "STR";

		param = icalproperty_get_first_parameter(
		    prop, ICAL_XLICERRORTYPE_PARAMETER);

		if (icalparameter_get_xlicerrortype(param) ==
		    ICAL_XLICERRORTYPE_VALUEPARSEERROR) {
		    
		    char propname[256];
		    if (sscanf(errstr,
			       "STR", propname) == 1) {
			
			if (!strcasecmp(propname, "STR")) continue;
			if (!strcasecmp(propname, "STR")) continue;
			if (!strcasecmp(propname, "STR")) continue;
		    }
		}
	    }
	}
    }

    return NULL;
}