dns_zone_getrequestexpire(dns_zone_t *zone) {
	REQUIRE(DNS_ZONE_VALID(zone));
	return (zone->requestexpire);
}