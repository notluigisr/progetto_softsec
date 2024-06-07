ldns_rdf_set_data(ldns_rdf *rd, void *data)
{
	
	assert(rd != NULL);
	rd->_data = data;
}