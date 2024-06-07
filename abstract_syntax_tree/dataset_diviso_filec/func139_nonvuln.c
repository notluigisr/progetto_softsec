update_encoding_table(table, interp, error_mode)
     VALUE table;
     VALUE interp;
     VALUE error_mode;
{
  struct tcltkip *ptr;
  int retry = 0;
  int i, idx, objc;
  Tcl_Obj **objv;
  Tcl_Obj *enc_list;
  volatile VALUE encname = Qnil;
  volatile VALUE encobj = Qnil;

  
  if (NIL_P(interp)) return 0;
  ptr = get_ip(interp);
  if (ptr == (struct tcltkip *) NULL)  return 0;
  if (deleted_ip(ptr)) return 0;

  
  Tcl_GetEncodingNames(ptr->ip);
  enc_list = Tcl_GetObjResult(ptr->ip);
  Tcl_IncrRefCount(enc_list);

  if (Tcl_ListObjGetElements(ptr->ip, enc_list,
			     &objc, &objv) != TCL_OK) {
    Tcl_DecrRefCount(enc_list);
    
    return 0;
  }

  
  for(i = 0; i < objc; i++) {
    encname = rb_str_new2(Tcl_GetString(objv[i]));
    if (NIL_P(rb_hash_lookup(table, encname))) {
      
      idx = rb_enc_find_index(StringValueCStr(encname));
      if (idx < 0) {
	encobj = create_dummy_encoding_for_tk_core(interp,encname,error_mode);
      } else {
	encobj = rb_enc_from_encoding(rb_enc_from_index(idx));
      }
      encname = rb_obj_freeze(encname);
      rb_hash_aset(table, encname, encobj);
      if (!NIL_P(encobj) && NIL_P(rb_hash_lookup(table, encobj))) {
	rb_hash_aset(table, encobj, encname);
      }
      retry = 1;
    }
  }

  Tcl_DecrRefCount(enc_list);

  return retry;
}