static void pixel_format_message (VncState *vs) {
    char pad[3] = { 0, 0, 0 };

    vnc_write_u8(vs, vs->ds->surface->pf.bits_per_pixel); 
    vnc_write_u8(vs, vs->ds->surface->pf.depth); 

#ifdef HOST_WORDS_BIGENDIAN
    vnc_write_u8(vs, 1);             
#else
    vnc_write_u8(vs, 0);             
#endif
    vnc_write_u8(vs, 1);             
    vnc_write_u16(vs, vs->ds->surface->pf.rmax);     
    vnc_write_u16(vs, vs->ds->surface->pf.gmax);     
    vnc_write_u16(vs, vs->ds->surface->pf.bmax);     
    vnc_write_u8(vs, vs->ds->surface->pf.rshift);    
    vnc_write_u8(vs, vs->ds->surface->pf.gshift);    
    vnc_write_u8(vs, vs->ds->surface->pf.bshift);    

    vnc_hextile_set_pixel_conversion(vs, 0);

    vs->clientds = *(vs->ds->surface);
    vs->clientds.flags &= ~QEMU_ALLOCATED_FLAG;
    vs->write_pixels = vnc_write_pixels_copy;

    vnc_write(vs, pad, 3);           
}