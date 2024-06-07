R_API ut64 r_bin_java_element_pair_calc_size(RBinJavaElementValuePair *evp) {
	ut64 sz = 0;
	if (evp == NULL) {
		return sz;
	}
	
	sz += 2;
	
	if (evp->value) {
		sz += r_bin_java_element_value_calc_size (evp->value);
	}
	return sz;
}