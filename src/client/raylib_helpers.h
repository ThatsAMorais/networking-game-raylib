// raylib_helpers.h
#ifndef RAYLIB_HELPERS_H
#define RAYLIB_HELPERS_H

#include "raylib.h"

// Undefine conflicting macros from Windows headers
#ifdef Rectangle
#undef Rectangle
#endif

#ifdef CloseWindow
#undef CloseWindow
#endif

#ifdef ShowCursor
#undef ShowCursor
#endif

// Redefine conflicting symbols as raylib-prefixed versions
#define raylib_DrawRectangle DrawRectangle
#define raylib_GetScreenWidth GetScreenWidth
#define raylib_GetScreenHeight GetScreenHeight
#define raylib_DrawTextEx DrawTextEx
#define raylib_DrawText DrawText

#endif // RAYLIB_HELPERS_H
