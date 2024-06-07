xmlSchemaGetParticleTotalRangeMin(xmlSchemaParticlePtr particle)
{
    if ((particle->children == NULL) ||
	(particle->minOccurs == 0))
	return (0);
    if (particle->children->type == XML_SCHEMA_TYPE_CHOICE) {
	int min = -1, cur;
	xmlSchemaParticlePtr part =
	    (xmlSchemaParticlePtr) particle->children->children;

	if (part == NULL)
	    return (0);
	while (part != NULL) {
	    if ((part->children->type == XML_SCHEMA_TYPE_ELEMENT) ||
		(part->children->type == XML_SCHEMA_TYPE_ANY))
		cur = part->minOccurs;
	    else
		cur = xmlSchemaGetParticleTotalRangeMin(part);
	    if (cur == 0)
		return (0);
	    if ((min > cur) || (min == -1))
		min = cur;
	    part = (xmlSchemaParticlePtr) part->next;
	}
	return (particle->minOccurs * min);
    } else {
	
	int sum = 0;
	xmlSchemaParticlePtr part =
	    (xmlSchemaParticlePtr) particle->children->children;

	if (part == NULL)
	    return (0);
	do {
	    if ((part->children->type == XML_SCHEMA_TYPE_ELEMENT) ||
		(part->children->type == XML_SCHEMA_TYPE_ANY))
		sum += part->minOccurs;
	    else
		sum += xmlSchemaGetParticleTotalRangeMin(part);
	    part = (xmlSchemaParticlePtr) part->next;
	} while (part != NULL);
	return (particle->minOccurs * sum);
    }
}