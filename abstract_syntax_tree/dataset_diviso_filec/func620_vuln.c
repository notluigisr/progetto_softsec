static int vmx_update_pi_irte(struct kvm *kvm, unsigned int host_irq,
			      uint32_t guest_irq, bool set)
{
	struct kvm_kernel_irq_routing_entry *e;
	struct kvm_irq_routing_table *irq_rt;
	struct kvm_lapic_irq irq;
	struct kvm_vcpu *vcpu;
	struct vcpu_data vcpu_info;
	int idx, ret = -EINVAL;

	if (!kvm_arch_has_assigned_device(kvm) ||
		!irq_remapping_cap(IRQ_POSTING_CAP) ||
		!kvm_vcpu_apicv_active(kvm->vcpus[0]))
		return 0;

	idx = srcu_read_lock(&kvm->irq_srcu);
	irq_rt = srcu_dereference(kvm->irq_routing, &kvm->irq_srcu);
	BUG_ON(guest_irq >= irq_rt->nr_rt_entries);

	hlist_for_each_entry(e, &irq_rt->map[guest_irq], link) {
		if (e->type != KVM_IRQ_ROUTING_MSI)
			continue;
		

		kvm_set_msi_irq(kvm, e, &irq);
		if (!kvm_intr_is_single_vcpu(kvm, &irq, &vcpu)) {
			
			ret = irq_set_vcpu_affinity(host_irq, NULL);
			if (ret < 0) {
				printk(KERN_INFO
				   "STR",
				   host_irq);
				goto out;
			}

			continue;
		}

		vcpu_info.pi_desc_addr = __pa(vcpu_to_pi_desc(vcpu));
		vcpu_info.vector = irq.vector;

		trace_kvm_pi_irte_update(vcpu->vcpu_id, host_irq, e->gsi,
				vcpu_info.vector, vcpu_info.pi_desc_addr, set);

		if (set)
			ret = irq_set_vcpu_affinity(host_irq, &vcpu_info);
		else {
			
			pi_set_sn(vcpu_to_pi_desc(vcpu));
			ret = irq_set_vcpu_affinity(host_irq, NULL);
			pi_clear_sn(vcpu_to_pi_desc(vcpu));
		}

		if (ret < 0) {
			printk(KERN_INFO "STR",
					__func__);
			goto out;
		}
	}

	ret = 0;
out:
	srcu_read_unlock(&kvm->irq_srcu, idx);
	return ret;
}