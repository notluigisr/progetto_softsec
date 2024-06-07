dname_strict_subdomain_c(uint8_t* d1, uint8_t* d2)
{
	return dname_strict_subdomain(d1, dname_count_labels(d1), d2,
		dname_count_labels(d2));
}