Linker* PackLinuxElf32mipsel::newLinker() const
{
    return new ElfLinkerMipsLE();
}