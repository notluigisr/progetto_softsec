static struct macsec_rx_sc *create_rx_sc(struct net_device *dev, sci_t sci)
{
	struct macsec_rx_sc *rx_sc;
	struct macsec_dev *macsec;
	struct net_device *real_dev = macsec_priv(dev)->real_dev;
	struct macsec_rxh_data *rxd = macsec_data_rtnl(real_dev);
	struct macsec_secy *secy;

	list_for_each_entry(macsec, &rxd->secys, secys) {
		if (find_rx_sc_rtnl(&macsec->secy, sci))
			return ERR_PTR(-EEXIST);
	}

	rx_sc = kzalloc(sizeof(*rx_sc), GFP_KERNEL);
	if (!rx_sc)
		return ERR_PTR(-ENOMEM);

	rx_sc->stats = netdev_alloc_pcpu_stats(struct pcpu_rx_sc_stats);
	if (!rx_sc->stats) {
		kfree(rx_sc);
		return ERR_PTR(-ENOMEM);
	}

	rx_sc->sci = sci;
	rx_sc->active = true;
	atomic_set(&rx_sc->refcnt, 1);

	secy = &macsec_priv(dev)->secy;
	rcu_assign_pointer(rx_sc->next, secy->rx_sc);
	rcu_assign_pointer(secy->rx_sc, rx_sc);

	if (rx_sc->active)
		secy->n_rx_sc++;

	return rx_sc;
}