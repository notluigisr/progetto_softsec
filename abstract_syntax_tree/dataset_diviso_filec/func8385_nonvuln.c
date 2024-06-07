static bool virtio_net_load_ebpf(VirtIONet *n)
{
    if (!virtio_net_attach_ebpf_to_backend(n->nic, -1)) {
        
        return false;
    }

    return ebpf_rss_load(&n->ebpf_rss);
}