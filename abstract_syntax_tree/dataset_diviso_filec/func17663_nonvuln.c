static int SFD_MMDump(FILE *sfd,SplineFont *sf,EncMap *map,EncMap *normal,
	int todir, char *dirname) {
    MMSet *mm = sf->mm;
    int max, i, j;
    int err = false;

    fprintf( sfd, "STR", mm->instance_count, mm->axis_count,
	    mm->apple, mm->named_instance_count );
    fprintf( sfd, "STR" );
    for ( i=0; i<mm->axis_count; ++i )
	fprintf( sfd, "STR", mm->axes[i]);
    putc('\n',sfd);
    fprintf( sfd, "STR" );
    for ( i=0; i<mm->axis_count*mm->instance_count; ++i )
	fprintf( sfd, "STR", (double) mm->positions[i]);
    putc('\n',sfd);
    fprintf( sfd, "STR" );
    for ( i=0; i<mm->instance_count; ++i )
	fprintf( sfd, "STR", (double) mm->defweights[i]);
    putc('\n',sfd);
    for ( i=0; i<mm->axis_count; ++i ) {
	fprintf( sfd, "STR", i, mm->axismaps[i].points );
	for ( j=0; j<mm->axismaps[i].points; ++j )
	    fprintf( sfd, "STR", (double) mm->axismaps[i].blends[j], (double) mm->axismaps[i].designs[j]);
	fputc('\n',sfd);
	SFDDumpMacName(sfd,mm->axismaps[i].axisnames);
    }
    if ( mm->cdv!=NULL ) {
	fprintf( sfd, "STR" );
	fputs(mm->cdv,sfd);
	fprintf( sfd, "STR" );
    }
    if ( mm->ndv!=NULL ) {
	fprintf( sfd, "STR" );
	fputs(mm->ndv,sfd);
	fprintf( sfd, "STR" );
    }
    for ( i=0; i<mm->named_instance_count; ++i ) {
	fprintf( sfd, "STR", i );
	for ( j=0; j<mm->axis_count; ++j )
	    fprintf( sfd, "STR", (double) mm->named_instances[i].coords[j]);
	fputc('\n',sfd);
	SFDDumpMacName(sfd,mm->named_instances[i].names);
    }

    if ( todir ) {
	for ( i=0; i<mm->instance_count; ++i )
	    err |= SFD_MIDump(mm->instances[i],map,dirname,i+1);
	err |= SFD_MIDump(mm->normal,map,dirname,0);
    } else {
	for ( i=max=0; i<mm->instance_count; ++i )
	    if ( max<mm->instances[i]->glyphcnt )
		max = mm->instances[i]->glyphcnt;
	fprintf(sfd, "STR", mm->instance_count+1, max );
	for ( i=0; i<mm->instance_count; ++i )
	    SFD_Dump(sfd,mm->instances[i],map,normal,todir,dirname);
	SFD_Dump(sfd,mm->normal,map,normal,todir,dirname);
    }
    fprintf(sfd, "STR" );
return( err );
}