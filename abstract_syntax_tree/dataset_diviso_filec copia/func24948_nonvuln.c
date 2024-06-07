__i915_gem_userptr_set_active(struct drm_i915_gem_object *obj, bool value)
{
	struct i915_mmu_object *mo = obj->userptr.mmu_object;

	
	if (!mo)
		return;

	spin_lock(&mo->mn->lock);
	if (value)
		add_object(mo);
	else
		del_object(mo);
	spin_unlock(&mo->mn->lock);
}