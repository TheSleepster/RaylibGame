/* ========================================================================
   $File: main.cpp $
   $Date: October 25 2025 05:50 pm $
   $Revision: $
   $Creator: Justin Lewis $
   ======================================================================== */
#include <stdio.h>

#include <raylib.h>
#include <raygui.h>

int
main(void)
{
    InitWindow(800, 800, "Raylib Window");
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLUE);
        EndDrawing();
    }

    return(0);
}
