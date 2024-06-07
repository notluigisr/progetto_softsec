static ssize_t node_read_numastat(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return sprintf(buf,
		       "STR"
		       "STR"
		       "STR"
		       "STR"
		       "STR"
		       "STR",
		       sum_zone_numa_state(dev->id, NUMA_HIT),
		       sum_zone_numa_state(dev->id, NUMA_MISS),
		       sum_zone_numa_state(dev->id, NUMA_FOREIGN),
		       sum_zone_numa_state(dev->id, NUMA_INTERLEAVE_HIT),
		       sum_zone_numa_state(dev->id, NUMA_LOCAL),
		       sum_zone_numa_state(dev->id, NUMA_OTHER));
}