routers_in_same_network_family(routerinfo_t *r1, routerinfo_t *r2)
{
  return (r1->addr & 0xffff0000) == (r2->addr & 0xffff0000);
}