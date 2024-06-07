R_API RBinJavaAttrInfo *r_bin_java_stack_map_table_attr_new(RBinJavaObj *bin, ut8 *buffer, ut64 sz, ut64 buf_offset) {
	ut32 i = 0;
	ut64 offset = 0;
	RBinJavaStackMapFrame *stack_frame = NULL, *new_stack_frame = NULL;
	if (sz < 10) {
		return NULL;
	}
	RBinJavaAttrInfo *attr = r_bin_java_default_attr_new (bin, buffer, sz, buf_offset);
	offset += 6;
	IFDBG eprintf("STR");
	if (!attr) {
		return NULL;
	}
	attr->info.stack_map_table_attr.stack_map_frame_entries = r_list_newf (r_bin_java_stack_frame_free);
	
	
	attr->info.stack_map_table_attr.number_of_entries = R_BIN_JAVA_USHORT (buffer, offset);
	offset += 2;
	IFDBG eprintf ("STR");
	IFDBG r_bin_java_print_stack_map_table_attr_summary(attr);
	for (i = 0; i < attr->info.stack_map_table_attr.number_of_entries; i++) {
		
		IFDBG eprintf ("STR", i, buf_offset + offset);
		if (stack_frame == NULL && R_BIN_JAVA_GLOBAL_BIN && R_BIN_JAVA_GLOBAL_BIN->current_code_attr) {
			IFDBG eprintf ("STR", i, buf_offset + offset);
			stack_frame = R_BIN_JAVA_GLOBAL_BIN->current_code_attr->info.code_attr.implicit_frame;
		}
		IFDBG eprintf ("STR", i, buf_offset + offset, stack_frame);
		if (offset >= sz) {
			r_bin_java_stack_map_table_attr_free (attr);
			return NULL;
		}
		new_stack_frame = r_bin_java_stack_map_frame_new (buffer + offset, sz - offset, stack_frame, buf_offset + offset);
		if (new_stack_frame) {
			offset += new_stack_frame->size;
			
			r_list_append (attr->info.stack_map_table_attr.stack_map_frame_entries, (void *) new_stack_frame);
			stack_frame = new_stack_frame;
		} else {
			eprintf ("STR");
			r_bin_java_stack_map_table_attr_free (attr);
			attr = NULL;
			break;
		}
	}
	if (attr) {
		attr->size = offset;
	}
	return attr;
}