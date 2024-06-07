static RList* sections(RBinFile *bf) {
	r_return_val_if_fail (bf && bf->o, NULL);
	QnxObj *qo = bf->o->bin_obj;
	return r_list_clone (qo->sections);
}