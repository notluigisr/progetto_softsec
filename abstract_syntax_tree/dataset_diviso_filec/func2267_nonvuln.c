int intel_iommu_enable_pasid(struct intel_iommu *iommu, struct intel_svm_dev *sdev)
{
	struct device_domain_info *info;
	struct context_entry *context;
	struct dmar_domain *domain;
	unsigned long flags;
	u64 ctx_lo;
	int ret;

	domain = get_valid_domain_for_dev(sdev->dev);
	if (!domain)
		return -EINVAL;

	spin_lock_irqsave(&device_domain_lock, flags);
	spin_lock(&iommu->lock);

	ret = -EINVAL;
	info = sdev->dev->archdata.iommu;
	if (!info || !info->pasid_supported)
		goto out;

	context = iommu_context_addr(iommu, info->bus, info->devfn, 0);
	if (WARN_ON(!context))
		goto out;

	ctx_lo = context[0].lo;

	sdev->did = domain->iommu_did[iommu->seq_id];
	sdev->sid = PCI_DEVID(info->bus, info->devfn);

	if (!(ctx_lo & CONTEXT_PASIDE)) {
		if (iommu->pasid_state_table)
			context[1].hi = (u64)virt_to_phys(iommu->pasid_state_table);
		context[1].lo = (u64)virt_to_phys(info->pasid_table->table) |
			intel_iommu_get_pts(sdev->dev);

		wmb();
		
		if ((ctx_lo & CONTEXT_TT_MASK) == (CONTEXT_TT_PASS_THROUGH << 2)) {
			ctx_lo &= ~CONTEXT_TT_MASK;
			if (info->ats_supported)
				ctx_lo |= CONTEXT_TT_PT_PASID_DEV_IOTLB << 2;
			else
				ctx_lo |= CONTEXT_TT_PT_PASID << 2;
		}
		ctx_lo |= CONTEXT_PASIDE;
		if (iommu->pasid_state_table)
			ctx_lo |= CONTEXT_DINVE;
		if (info->pri_supported)
			ctx_lo |= CONTEXT_PRS;
		context[0].lo = ctx_lo;
		wmb();
		iommu->flush.flush_context(iommu, sdev->did, sdev->sid,
					   DMA_CCMD_MASK_NOBIT,
					   DMA_CCMD_DEVICE_INVL);
	}

	
	if (!info->pasid_enabled)
		iommu_enable_dev_iotlb(info);

	if (info->ats_enabled) {
		sdev->dev_iotlb = 1;
		sdev->qdep = info->ats_qdep;
		if (sdev->qdep >= QI_DEV_EIOTLB_MAX_INVS)
			sdev->qdep = 0;
	}
	ret = 0;

 out:
	spin_unlock(&iommu->lock);
	spin_unlock_irqrestore(&device_domain_lock, flags);

	return ret;
}