static void uc_fw_unbind_ggtt(struct intel_uc_fw *uc_fw)
{
	struct drm_i915_gem_object *obj = uc_fw->obj;
	struct i915_ggtt *ggtt = __uc_fw_to_gt(uc_fw)->ggtt;
	u64 start = uc_fw_ggtt_offset(uc_fw);

	ggtt->vm.clear_range(&ggtt->vm, start, obj->base.size);
}