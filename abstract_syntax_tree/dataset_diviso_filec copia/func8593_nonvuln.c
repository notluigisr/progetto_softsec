vips_foreign_load_temp( VipsForeignLoad *load )
{
	const guint64 disc_threshold = vips_get_disc_threshold();
	const guint64 image_size = VIPS_IMAGE_SIZEOF_IMAGE( load->out );

	
	if( load->flags & VIPS_FOREIGN_PARTIAL ) {
#ifdef DEBUG
		printf( "STR" );
#endif 

		return( vips_image_new() );
	}

	
	if( (load->flags & VIPS_FOREIGN_SEQUENTIAL) && 
		load->access != VIPS_ACCESS_RANDOM ) {
#ifdef DEBUG
		printf( "STR" );
#endif 

		return( vips_image_new() );
	}

	
	if( !load->disc )
		load->memory = TRUE;

	
	if( !load->memory && 
		image_size > disc_threshold ) {
#ifdef DEBUG
		printf( "STR" );
#endif 

		return( vips_image_new_temp_file( "STR" ) );
	}

#ifdef DEBUG
	printf( "STR" );
#endif 

	
	return( vips_image_new_memory() );
}