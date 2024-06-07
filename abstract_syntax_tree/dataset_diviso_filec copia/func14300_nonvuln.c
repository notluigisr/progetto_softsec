i915_gem_execbuffer_relocate(struct drm_device *dev,
			     struct eb_objects *eb,
			     struct list_head *objects)
{
	struct drm_i915_gem_object *obj;
	int ret = 0;

	
	pagefault_disable();
	list_for_each_entry(obj, objects, exec_list) {
		ret = i915_gem_execbuffer_relocate_object(obj, eb);
		if (ret)
			break;
	}
	pagefault_enable();

	return ret;
}