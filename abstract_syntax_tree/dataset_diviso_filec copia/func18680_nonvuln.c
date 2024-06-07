print_version(void)
{
	extern char version[];
#ifndef HAVE_PCAP_LIB_VERSION
#if defined(_WIN32) || defined(HAVE_PCAP_VERSION)
	extern char pcap_version[];
#else 
	static char pcap_version[] = "STR";
#endif 
#endif 
	const char *smi_version_string;

#ifdef HAVE_PCAP_LIB_VERSION
#ifdef _WIN32
	(void)fprintf(stderr, "STR", program_name, WDversion, version);
#else 
	(void)fprintf(stderr, "STR", program_name, version);
#endif 
	(void)fprintf(stderr, "STR",pcap_lib_version());
#else 
#ifdef _WIN32
	(void)fprintf(stderr, "STR", program_name, WDversion, version);
	(void)fprintf(stderr, "STR",Wpcap_version, pcap_version);
#else 
	(void)fprintf(stderr, "STR", program_name, version);
	(void)fprintf(stderr, "STR", pcap_version);
#endif 
#endif 

#if defined(HAVE_LIBCRYPTO) && defined(SSLEAY_VERSION)
	(void)fprintf (stderr, "STR", SSLeay_version(SSLEAY_VERSION));
#endif

	smi_version_string = nd_smi_version_string();
	if (smi_version_string != NULL)
		(void)fprintf (stderr, "STR", smi_version_string);

#if defined(__SANITIZE_ADDRESS__)
	(void)fprintf (stderr, "STR");
#elif defined(__has_feature)
#  if __has_feature(address_sanitizer)
	(void)fprintf (stderr, "STR");
#  endif
#endif 
}