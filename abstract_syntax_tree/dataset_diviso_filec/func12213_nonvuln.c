bool CIRCSock::IsFloodProtected(double fRate) {
    return fRate > FLOOD_MINIMAL_RATE;
}