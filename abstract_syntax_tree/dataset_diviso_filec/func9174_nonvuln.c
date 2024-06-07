static int create_vcpu_fd(struct kvm_vcpu *vcpu)
{
	return anon_inode_getfd("STR", &kvm_vcpu_fops, vcpu, O_RDWR);
}