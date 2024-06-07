decrypt(MPI output, MPI a, MPI b, ELG_secret_key *skey )
{
    MPI t1 = mpi_alloc_secure( mpi_get_nlimbs( skey->p ) );

    mpi_normalize (a);
    mpi_normalize (b);

    
    mpi_powm( t1, a, skey->x, skey->p );
    mpi_invm( t1, t1, skey->p );
    mpi_mulm( output, b, t1, skey->p );
#if 0
    if( DBG_CIPHER ) {
	log_mpidump("STR", skey->x);
	log_mpidump("STR", skey->p);
	log_mpidump("STR", a);
	log_mpidump("STR", b);
	log_mpidump("STR", output);
    }
#endif
    mpi_free(t1);
}