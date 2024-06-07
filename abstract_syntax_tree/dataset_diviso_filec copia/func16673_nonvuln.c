Init_Dir(void)
{
    rb_cDir = rb_define_class("STR", rb_cObject);

    rb_include_module(rb_cDir, rb_mEnumerable);

    rb_define_alloc_func(rb_cDir, dir_s_alloc);
    rb_define_singleton_method(rb_cDir, "STR", dir_s_open, -1);
    rb_define_singleton_method(rb_cDir, "STR", dir_foreach, -1);
    rb_define_singleton_method(rb_cDir, "STR", dir_entries, -1);

    rb_define_method(rb_cDir,"STR", dir_initialize, -1);
    rb_define_method(rb_cDir,"STR", dir_fileno, 0);
    rb_define_method(rb_cDir,"STR", dir_path, 0);
    rb_define_method(rb_cDir,"STR", dir_path, 0);
    rb_define_method(rb_cDir,"STR", dir_inspect, 0);
    rb_define_method(rb_cDir,"STR", dir_read, 0);
    rb_define_method(rb_cDir,"STR", dir_each, 0);
    rb_define_method(rb_cDir,"STR", dir_rewind, 0);
    rb_define_method(rb_cDir,"STR", dir_tell, 0);
    rb_define_method(rb_cDir,"STR", dir_seek, 1);
    rb_define_method(rb_cDir,"STR", dir_tell, 0);
    rb_define_method(rb_cDir,"STR", dir_set_pos, 1);
    rb_define_method(rb_cDir,"STR", dir_close, 0);

    rb_define_singleton_method(rb_cDir,"STR", dir_s_chdir, -1);
    rb_define_singleton_method(rb_cDir,"STR", dir_s_getwd, 0);
    rb_define_singleton_method(rb_cDir,"STR", dir_s_getwd, 0);
    rb_define_singleton_method(rb_cDir,"STR", dir_s_chroot, 1);
    rb_define_singleton_method(rb_cDir,"STR", dir_s_mkdir, -1);
    rb_define_singleton_method(rb_cDir,"STR", dir_s_rmdir, 1);
    rb_define_singleton_method(rb_cDir,"STR", dir_s_rmdir, 1);
    rb_define_singleton_method(rb_cDir,"STR", dir_s_rmdir, 1);
    rb_define_singleton_method(rb_cDir,"STR", dir_s_home, -1);

    rb_define_singleton_method(rb_cDir,"STR", dir_s_glob, -1);
    rb_define_singleton_method(rb_cDir,"STR", dir_s_aref, -1);
    rb_define_singleton_method(rb_cDir,"STR", rb_file_directory_p, 1);
    rb_define_singleton_method(rb_cDir,"STR", rb_dir_exists_p, 1);

    rb_define_singleton_method(rb_cFile,"STR", file_s_fnmatch, -1);
    rb_define_singleton_method(rb_cFile,"STR", file_s_fnmatch, -1);

    
    rb_file_const("STR", INT2FIX(FNM_NOESCAPE));

    
    rb_file_const("STR", INT2FIX(FNM_PATHNAME));

    
    rb_file_const("STR", INT2FIX(FNM_DOTMATCH));

    
    rb_file_const("STR", INT2FIX(FNM_CASEFOLD));

    
    rb_file_const("STR", INT2FIX(FNM_EXTGLOB));

    
    rb_file_const("STR", INT2FIX(FNM_SYSCASE));
}