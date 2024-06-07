psf_log_SF_INFO (SF_PRIVATE *psf)
{	psf_log_printf (psf, "STR") ;

	psf_log_printf (psf, "STR", psf->sf.samplerate) ;
	if (psf->sf.frames == SF_COUNT_MAX)
		psf_log_printf (psf, "STR") ;
	else
		psf_log_printf (psf, "STR", psf->sf.frames) ;
	psf_log_printf (psf, "STR", psf->sf.channels) ;

	psf_log_printf (psf, "STR", psf->sf.format) ;
	psf_log_printf (psf, "STR", psf->sf.sections) ;
	psf_log_printf (psf, "STR") ;

	psf_log_printf (psf, "STR") ;
} 