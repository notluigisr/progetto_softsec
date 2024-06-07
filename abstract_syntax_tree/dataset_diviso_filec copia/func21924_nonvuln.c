void cil_destroy_classperms_list(struct cil_list **cp_list)
{
	struct cil_list_item *curr;

	if (cp_list == NULL || *cp_list == NULL) {
		return;
	}

	cil_list_for_each(curr, *cp_list) {
		if (curr->flavor == CIL_CLASSPERMS) {
			cil_destroy_classperms(curr->data);
		} else {
			cil_destroy_classperms_set(curr->data);
		}
	}

	cil_list_destroy(cp_list, CIL_FALSE);
}