#include <Resources.h>

unsigned char *loadImage(const char *filePath, int *width, int *height,
                         bool flipHorizontally, bool flipVertically) {

  SDL_Surface *surface = IMG_Load(filePath);
  if (!surface) {
    fprintf(stderr, "Failed to load image: %s\n", SDL_GetError());
    return nullptr;
  }

  if (flipHorizontally) {

    if (!SDL_FlipSurface(surface, SDL_FLIP_HORIZONTAL)) {
      fprintf(stderr, "Failed to flip texure horizontally: %s\n",
              SDL_GetError());
    }
    return nullptr;
  }

  if (flipVertically) {
    if (!SDL_FlipSurface(surface, SDL_FLIP_VERTICAL)) {
      fprintf(stderr, "Failed to flip texure vertically: %s\n", SDL_GetError());
      return nullptr;
    }
  }

  *width = surface->w;
  *height = surface->h;

  size_t dataSize =
      (*width) * (*height) * (SDL_BITSPERPIXEL(surface->format) / 8);
  unsigned char *byteDataImg = (unsigned char *)malloc(dataSize);

  if (!byteDataImg) {
    fprintf(stderr, "Memory allocation failed.\n");
    SDL_DestroySurface(surface);
    return nullptr;
  }

  memcpy(byteDataImg, surface->pixels, dataSize);
  SDL_DestroySurface(surface);

  return byteDataImg;
}