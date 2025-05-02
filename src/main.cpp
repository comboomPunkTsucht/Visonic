// Copyright (c) 2025 mahd
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "../external/header/nob.h/nob.h"
#include "../external/lib/raylib/src/raylib.h"
#include "../external/lib/raygui/src/raygui.h"
#include "./header/nord.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_TITLE "Visonic"

Color hex_to_color(int hex) {
  return (Color){
      .r = (unsigned char)((hex >> 24) & 0xFF),
      .g = (unsigned char)((hex >> 16) & 0xFF),
      .b = (unsigned char)((hex >> 8) & 0xFF),
      .a = (unsigned char)(hex & 0xFF),
  };
}

Color hex_to_color_with_custom_alpha(int hex, int alpha)
{
  return (Color){
      .r = (unsigned char)((hex >> 24) & 0xFF),
      .g = (unsigned char)((hex >> 16) & 0xFF),
      .b = (unsigned char)((hex >> 8) & 0xFF),
      .a = (unsigned char)(alpha & 0xFF),
  };
}
int main(int argc, char **argv){
  NOB_UNUSED(argc);
  NOB_UNUSED(argv);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
  SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_ALWAYS_RUN | FLAG_WINDOW_MAXIMIZED | FLAG_BORDERLESS_WINDOWED_MODE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_INTERLACED_HINT);
  SetTargetFPS(60);
  int fontSize = 69;
  Font font = LoadFontEx("./src/font/CaskaydiaCoveNerdFontPropo-Regular.ttf", fontSize, NULL, 0);

  while (!WindowShouldClose()) {
    char *text = "Hello, Visonic!";
    Vector2 textDim = MeasureTextEx(font, text, fontSize, 0);
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();



    BeginDrawing();
    ClearBackground(hex_to_color_with_custom_alpha(NORD_0, 0));
    DrawTextEx(font,text, (Vector2){.x = screenWidth/2 - textDim.x/2, .y = screenHeight/2 - textDim.y/2 }, fontSize, 0, hex_to_color(NORD_6));
    EndDrawing();
  }

  CloseWindow();
  return 0;
}