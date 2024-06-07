i915_gem_execbuffer2_ioctl(struct drm_device *dev, void *data,
			   struct drm_file *file)
{
	struct drm_i915_gem_execbuffer2 *args = data;
	struct drm_i915_gem_exec_object2 *exec2_list;
	struct drm_syncobj **fences = NULL;
	const size_t count = args->buffer_count;
	int err;

	if (!check_buffer_count(count)) {
		DRM_DEBUG("STR", count);
		return -EINVAL;
	}

	if (!i915_gem_check_execbuffer(args))
		return -EINVAL;

	
	exec2_list = kvmalloc_array(count + 1, eb_element_size(),
				    __GFP_NOWARN | GFP_KERNEL);
	if (exec2_list == NULL) {
		DRM_DEBUG("STR",
			  count);
		return -ENOMEM;
	}
	if (copy_from_user(exec2_list,
			   u64_to_user_ptr(args->buffers_ptr),
			   sizeof(*exec2_list) * count)) {
		DRM_DEBUG("STR", count);
		kvfree(exec2_list);
		return -EFAULT;
	}

	if (args->flags & I915_EXEC_FENCE_ARRAY) {
		fences = get_fence_array(args, file);
		if (IS_ERR(fences)) {
			kvfree(exec2_list);
			return PTR_ERR(fences);
		}
	}

	err = i915_gem_do_execbuffer(dev, file, args, exec2_list, fences);

	
	if (args->flags & __EXEC_HAS_RELOC) {
		struct drm_i915_gem_exec_object2 __user *user_exec_list =
			u64_to_user_ptr(args->buffers_ptr);
		unsigned int i;

		
		user_access_begin();
		for (i = 0; i < args->buffer_count; i++) {
			if (!(exec2_list[i].offset & UPDATE))
				continue;

			exec2_list[i].offset =
				gen8_canonical_addr(exec2_list[i].offset & PIN_OFFSET_MASK);
			unsafe_put_user(exec2_list[i].offset,
					&user_exec_list[i].offset,
					end_user);
		}
end_user:
		user_access_end();
	}

	args->flags &= ~__I915_EXEC_UNKNOWN_FLAGS;
	put_fence_array(args, fences);
	kvfree(exec2_list);
	return err;
}