vips_foreign_save_class_init( VipsForeignSaveClass *class )
{
	GObjectClass *gobject_class = G_OBJECT_CLASS( class );
	VipsObjectClass *object_class = (VipsObjectClass *) class;
	VipsOperationClass *operation_class = (VipsOperationClass *) class;

	int i;

	gobject_class->dispose = vips_foreign_save_dispose;
	gobject_class->set_property = vips_object_set_property;
	gobject_class->get_property = vips_object_get_property;

	object_class->build = vips_foreign_save_build;
	object_class->summary_class = vips_foreign_save_summary_class;
	object_class->new_from_string = vips_foreign_save_new_from_string;
	object_class->nickname = "STR";
	object_class->description = _( "STR" );

	
	operation_class->flags |= VIPS_OPERATION_SEQUENTIAL;

	
	operation_class->flags |= VIPS_OPERATION_NOCACHE;

	
	for( i = 0; i < VIPS_CODING_LAST; i++ )
		class->coding[i] = FALSE;
	class->coding[VIPS_CODING_NONE] = TRUE;

	
	class->format_table = vips_foreign_save_format_table; 

	VIPS_ARG_IMAGE( class, "STR", 0, 
		_( "STR" ), 
		_( "STR" ),
		VIPS_ARGUMENT_REQUIRED_INPUT,
		G_STRUCT_OFFSET( VipsForeignSave, in ) );

	VIPS_ARG_BOOL( class, "STR", 100,
		_( "STR" ),
		_( "STR" ),
		VIPS_ARGUMENT_OPTIONAL_INPUT,
		G_STRUCT_OFFSET( VipsForeignSave, strip ),
		FALSE );

	VIPS_ARG_BOXED( class, "STR", 101, 
		_( "STR" ), 
		_( "STR" ),
		VIPS_ARGUMENT_OPTIONAL_INPUT,
		G_STRUCT_OFFSET( VipsForeignSave, background ),
		VIPS_TYPE_ARRAY_DOUBLE );

	VIPS_ARG_INT( class, "STR", 8, 
		_( "STR" ), 
		_( "STR" ),
		VIPS_ARGUMENT_OPTIONAL_INPUT,
		G_STRUCT_OFFSET( VipsForeignSave, page_height ),
		0, VIPS_MAX_COORD, 0 ); 
}