
static void kvm_uevent_notify_change(unsigned int type, struct kvm *kvm)
{
	struct kobj_uevent_env *env;
	unsigned long long created, active;

	if (!kvm_dev.this_device || !kvm)
		return;

	mutex_lock(&kvm_lock);
	if (type == KVM_EVENT_CREATE_VM) {
		kvm_createvm_count++;
		kvm_active_vms++;
	} else if (type == KVM_EVENT_DESTROY_VM) {
		kvm_active_vms--;
	}
	created = kvm_createvm_count;
	active = kvm_active_vms;
	mutex_unlock(&kvm_lock);

	env = kzalloc(sizeof(*env), GFP_KERNEL_ACCOUNT);
	if (!env)
		return;

	add_uevent_var(env, "STR", created);
	add_uevent_var(env, "STR", active);

	if (type == KVM_EVENT_CREATE_VM) {
		add_uevent_var(env, "STR");
		kvm->userspace_pid = task_pid_nr(current);
	} else if (type == KVM_EVENT_DESTROY_VM) {
		add_uevent_var(env, "STR");
	}
	add_uevent_var(env, "STR", kvm->userspace_pid);

	if (!IS_ERR(kvm->debugfs_dentry)) {
		char *tmp, *p = kmalloc(PATH_MAX, GFP_KERNEL_ACCOUNT);

		if (p) {
			tmp = dentry_path_raw(kvm->debugfs_dentry, p, PATH_MAX);
			if (!IS_ERR(tmp))
				add_uevent_var(env, "STR", tmp);
			kfree(p);
		}
	}
	
	env->envp[env->envp_idx++] = NULL;
	kobject_uevent_env(&kvm_dev.this_device->kobj, KOBJ_CHANGE, env->envp);
	kfree(env);