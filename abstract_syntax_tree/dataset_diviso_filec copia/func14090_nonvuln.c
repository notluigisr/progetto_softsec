static int parseFunctionHeader(struct cli_bc *bc, unsigned fn, unsigned char *buffer)
{
    char ok=1;
    unsigned offset, len, all_locals=0, i;
    struct cli_bc_func *func;

    if (fn >= bc->num_func) {
	cli_errmsg("STR", fn,
		   bc->num_func);
	return CL_EMALFDB;
    }
    func = &bc->funcs[fn];
    len = strlen((const char*)buffer);

    if (buffer[0] != 'A') {
	cli_errmsg("STR", buffer[0]);
	return CL_EMALFDB;
    }
    offset = 1;
    func->numArgs = readFixedNumber(buffer, &offset, len, &ok, 1);
    func->returnType = readTypeID(bc, buffer, &offset, len, &ok);
    if (buffer[offset] != 'L') {
	cli_errmsg("STR", buffer[offset]);
	return CL_EMALFDB;
    }
    offset++;
    func->numLocals = readNumber(buffer, &offset, len, &ok);
    if (!ok) {
	cli_errmsg("STR");
	return CL_EMALFDB;
    }
    all_locals = func->numArgs + func->numLocals;
    if (!all_locals) {
	func->types = NULL;
    } else {
	func->types = cli_calloc(all_locals, sizeof(*func->types));
	if (!func->types) {
	    cli_errmsg("STR");
	    return CL_EMEM;
	}
    }
    for (i=0;i<all_locals;i++) {
	func->types[i] = readNumber(buffer, &offset, len, &ok);
	if (readFixedNumber(buffer, &offset, len, &ok, 1))
	    func->types[i] |= 0x8000;
    }
    if (!ok) {
	cli_errmsg("STR");
	return CL_EMALFDB;
    }
    if (buffer[offset] != 'F') {
	cli_errmsg("STR", buffer[offset]);
	return CL_EMALFDB;
    }
    offset++;
    func->numInsts = readNumber(buffer, &offset, len, &ok);
    if (!ok ){
	cli_errmsg("STR");
	return CL_EMALFDB;
    }
    func->numValues = func->numArgs + func->numLocals;
    func->insn_idx = 0;
    func->numConstants=0;
    func->allinsts = cli_calloc(func->numInsts, sizeof(*func->allinsts));
    if (!func->allinsts) {
	cli_errmsg("STR");
	return CL_EMEM;
    }
    func->numBB = readNumber(buffer, &offset, len, &ok);
    if (!ok) {
	cli_errmsg("STR");
	return CL_EMALFDB;
    }
    func->BB = cli_calloc(func->numBB, sizeof(*func->BB));
    if (!func->BB) {
	cli_errmsg("STR");
	return CL_EMEM;
    }
    return CL_SUCCESS;
}