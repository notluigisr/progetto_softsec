RZ_API ut64 rz_bin_object_addr_with_base(RzBinObject *o, ut64 addr) {
	return o ? addr + o->baddr_shift : addr;
}