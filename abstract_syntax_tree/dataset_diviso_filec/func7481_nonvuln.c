static uint64_t zynq_slcr_compute_clock(const uint64_t periods[],
                                        uint32_t ctrl_reg,
                                        unsigned index)
{
    uint32_t srcsel = extract32(ctrl_reg, 4, 2); 
    uint32_t divisor = extract32(ctrl_reg, 8, 6); 

    
    if (((ctrl_reg >> index) & 1u) == 0) {
        return 0;
    }

    
    
    return periods[srcsel] * (divisor ? divisor : 1u);
}