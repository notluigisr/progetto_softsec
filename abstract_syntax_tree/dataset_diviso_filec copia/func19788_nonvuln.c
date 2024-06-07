bgp_rte_update(struct bgp_proto *p, ip_addr prefix, int pxlen,
	       u32 path_id, u32 *last_id, struct rte_src **src,
	       rta *a0, rta **a)
{
  if (path_id != *last_id)
    {
      *src = rt_get_source(&p->p, path_id);
      *last_id = path_id;

      if (*a)
	{
	  rta_free(*a);
	  *a = NULL;
	}
    }

  
  if (!*a)
    {
      a0->src = *src;

      
      ea_list *ea = a0->eattrs;
      *a = rta_lookup(a0);
      a0->eattrs = ea;
    }

  net *n = net_get(p->p.table, prefix, pxlen);
  rte *e = rte_get_temp(rta_clone(*a));
  e->net = n;
  e->pflags = 0;
  e->u.bgp.suppressed = 0;
  e->u.bgp.stale = -1;
  rte_update2(p->p.main_ahook, n, e, *src);
}