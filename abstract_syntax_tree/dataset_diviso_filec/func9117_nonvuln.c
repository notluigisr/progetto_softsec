SDL_FreeBlitMap(SDL_BlitMap * map)
{
    if (map) {
        SDL_InvalidateMap(map);
        SDL_free(map);
    }
}