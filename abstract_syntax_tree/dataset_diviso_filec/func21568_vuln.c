static void vnc_tight_stop(VncState *vs)
{
    
    vs->tight.tight = vs->output;
    vs->output = vs->tight.tmp;
}