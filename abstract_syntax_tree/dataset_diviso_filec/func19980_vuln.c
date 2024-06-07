dir_initialize(int argc, VALUE *argv, VALUE dir)
{
    struct dir_data *dp;
    rb_encoding  *fsenc;
    VALUE dirname, opt, orig;
    static ID keyword_ids[1];
    const char *path;

    if (!keyword_ids[0]) {
	keyword_ids[0] = rb_id_encoding();
    }

    fsenc = rb_filesystem_encoding();

    rb_scan_args(argc, argv, "STR", &dirname, &opt);

    if (!NIL_P(opt)) {
	VALUE enc;
	rb_get_kwargs(opt, keyword_ids, 0, 1, &enc);
	if (enc != Qundef && !NIL_P(enc)) {
	    fsenc = rb_to_encoding(enc);
	}
    }

    GlobPathValue(dirname, FALSE);
    orig = rb_str_dup_frozen(dirname);
    dirname = rb_str_encode_ospath(dirname);
    dirname = rb_str_dup_frozen(dirname);

    TypedData_Get_Struct(dir, struct dir_data, &dir_data_type, dp);
    if (dp->dir) closedir(dp->dir);
    dp->dir = NULL;
    RB_OBJ_WRITE(dir, &dp->path, Qnil);
    dp->enc = fsenc;
    path = RSTRING_PTR(dirname);
    dp->dir = opendir_without_gvl(path);
    if (dp->dir == NULL) {
	int e = errno;
	if (rb_gc_for_fd(e)) {
	    dp->dir = opendir_without_gvl(path);
	}
#ifdef HAVE_GETATTRLIST
	else if (e == EIO) {
	    u_int32_t attrbuf[1];
	    struct attrlist al = {ATTR_BIT_MAP_COUNT, 0};
	    if (getattrlist(path, &al, attrbuf, sizeof(attrbuf), FSOPT_NOFOLLOW) == 0) {
		dp->dir = opendir_without_gvl(path);
	    }
	}
#endif
	if (dp->dir == NULL) {
	    RB_GC_GUARD(dirname);
	    rb_syserr_fail_path(e, orig);
	}
    }
    RB_OBJ_WRITE(dir, &dp->path, orig);

    return dir;
}