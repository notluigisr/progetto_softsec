has_interface(gqlType type, gqlType interface) {
    gqlTypeLink    	tl;

    for (tl = type->interfaces; NULL != tl; tl = tl->next) {
	if (tl->type == type) {
	    return true;
	}
    }
    return false;
}