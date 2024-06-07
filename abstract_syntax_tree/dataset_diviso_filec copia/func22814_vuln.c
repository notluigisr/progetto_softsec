void sas_deform_port(struct asd_sas_phy *phy, int gone)
{
	struct sas_ha_struct *sas_ha = phy->ha;
	struct asd_sas_port *port = phy->port;
	struct sas_internal *si =
		to_sas_internal(sas_ha->core.shost->transportt);
	struct domain_device *dev;
	unsigned long flags;

	if (!port)
		return;		  

	dev = port->port_dev;
	if (dev)
		dev->pathways--;

	if (port->num_phys == 1) {
		sas_unregister_domain_devices(port, gone);
		sas_port_delete(port->port);
		port->port = NULL;
	} else {
		sas_port_delete_phy(port->port, phy->phy);
		sas_device_set_phy(dev, port->port);
	}

	if (si->dft->lldd_port_deformed)
		si->dft->lldd_port_deformed(phy);

	spin_lock_irqsave(&sas_ha->phy_port_lock, flags);
	spin_lock(&port->phy_list_lock);

	list_del_init(&phy->port_phy_el);
	sas_phy_set_target(phy, NULL);
	phy->port = NULL;
	port->num_phys--;
	port->phy_mask &= ~(1U << phy->id);

	if (port->num_phys == 0) {
		INIT_LIST_HEAD(&port->phy_list);
		memset(port->sas_addr, 0, SAS_ADDR_SIZE);
		memset(port->attached_sas_addr, 0, SAS_ADDR_SIZE);
		port->class = 0;
		port->iproto = 0;
		port->tproto = 0;
		port->oob_mode = 0;
		port->phy_mask = 0;
	}
	spin_unlock(&port->phy_list_lock);
	spin_unlock_irqrestore(&sas_ha->phy_port_lock, flags);

	return;
}