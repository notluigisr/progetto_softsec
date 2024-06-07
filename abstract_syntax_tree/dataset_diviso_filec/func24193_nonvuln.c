static void mwifiex_pcie_card_reset_work(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;

	
	pci_try_reset_function(card->dev);
}