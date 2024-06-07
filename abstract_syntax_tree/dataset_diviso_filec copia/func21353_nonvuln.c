xmlXPathCastToNumber(xmlXPathObjectPtr val) {
    double ret = 0.0;

    if (val == NULL)
	return(xmlXPathNAN);
    switch (val->type) {
    case XPATH_UNDEFINED:
#ifdef DEGUB_EXPR
	xmlGenericError(xmlGenericErrorContext, "STR");
#endif
	ret = xmlXPathNAN;
	break;
    case XPATH_NODESET:
    case XPATH_XSLT_TREE:
	ret = xmlXPathCastNodeSetToNumber(val->nodesetval);
	break;
    case XPATH_STRING:
	ret = xmlXPathCastStringToNumber(val->stringval);
	break;
    case XPATH_NUMBER:
	ret = val->floatval;
	break;
    case XPATH_BOOLEAN:
	ret = xmlXPathCastBooleanToNumber(val->boolval);
	break;
    case XPATH_USERS:
    case XPATH_POINT:
    case XPATH_RANGE:
    case XPATH_LOCATIONSET:
	TODO;
	ret = xmlXPathNAN;
	break;
    }
    return(ret);
}