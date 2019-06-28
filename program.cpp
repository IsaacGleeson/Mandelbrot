#include "splashkit.h"
#include <string>
#include <math.h>
#define MAX_ITERATION 1000.0 //sets MAX ITERATION to a constant 1000.0

color iteration_color (int iteration)
{
    double hue;
    if(iteration >= MAX_ITERATION)
    {
        return (COLOR_BLACK);
    }

    else
    {
        hue = 0.5 + (iteration / MAX_ITERATION);
        
        if(hue > 1)
        {
            hue = hue - 1;
        }

        return hsb_color(hue, 0.8, 0.9);
    }
}

color mandelbrot_color(double mb_x, double mb_y)
//Colours the Mandelbrot 
{
    double xtemp;
    double x;
    double y;
    int iteration;

    x = mb_x;
    y = mb_y;

    iteration = 0;

    while(( (x*x) + (y*y) <= 4) and (iteration < MAX_ITERATION))
    {
        xtemp = (x*x) - (y*y) + mb_x;
        y = 2 * x * y + mb_y;
        x = xtemp;
        iteration = iteration + 1;
    }

    return iteration_color(iteration);
}

void draw_mand(double start_mb_x, double start_mb_y, double mb_width, double mb_height)
{ // Draws the mandelbrot 
    double scale_width, scale_height; 
    double mx, my;
    int x,y;
    color mb_color; 

    scale_width = mb_width / screen_width();
    scale_height = mb_height / screen_height();
    x = 0;

    while(x < screen_width())
    {
        y = 0;

        while(y < screen_height())
        {
            mx = start_mb_x + x * scale_width;
            my = start_mb_y + y * scale_height;
            mb_color = mandelbrot_color(mx, my);
            draw_pixel(mb_color, x, y);

            y = y + 1;
        }
        x = x + 1;
    }
}

int main()
{
    double start_mb_x, start_mb_y;
    double new_start_mb_x, new_start_mb_y;
    double mb_width, mb_height;
    double new_mb_width, new_mb_height;
    double zoom_amount;

    start_mb_x = -2.5;
    start_mb_y = -1.5;

    mb_width = 4;
    mb_height = 3;

    open_window("Mandelbrot", 320, 240); 

    while(not quit_requested()) //While Active
    {
        process_events();

        draw_mand(start_mb_x, start_mb_y, mb_width, mb_height);

        refresh_screen(60); // refreshes the window every zoom(iteration)

        if(mouse_clicked(LEFT_BUTTON)) 
        // Zoom in when left button is pressed 
        // Zooms in on the x/y co-ords of the mouse
        // mouse_y = y pos
        // mouse_x = x pos
        {
            new_mb_height = mb_height / 2;
            new_start_mb_y = start_mb_y + mouse_y() / screen_height() * mb_height;
            new_mb_width = mb_width  /2;
            new_start_mb_x = start_mb_x + mouse_x() / screen_width() * mb_width;

            mb_width = new_mb_width;
            mb_height = new_mb_height;
            start_mb_x = new_start_mb_x;
            start_mb_y = new_start_mb_y;

            if(zoom_amount == -1)
            {
                zoom_amount = 1;
            }
            else if(zoom_amount < 0)
            {
                zoom_amount = zoom_amount / 2;
            }
            else
            {
                zoom_amount = zoom_amount * 2;
            }
        }

        if(mouse_clicked(RIGHT_BUTTON)) 
        // Zoom out when right button is pressed
        // Zooms in on the x/y co-ords of the mouse
        // mouse_y = y pos
        // mouse_x = x pos
        {
            new_mb_height = mb_height * 2;
            new_start_mb_y = start_mb_y + mouse_y() / screen_height() * mb_height;
            new_mb_width = mb_width * 2;
            new_start_mb_x = start_mb_x + mouse_x() / screen_width() * mb_width;

            mb_width = new_mb_width;
            mb_height = new_mb_height;
            start_mb_x = new_start_mb_x;
            start_mb_y = new_start_mb_y;

            if(zoom_amount == -1)
            {
                zoom_amount = 1;
            }
            else if(zoom_amount < 0)
            {
                zoom_amount = zoom_amount * 2;
            }
            else
            {
                zoom_amount = zoom_amount * 2;
            } 
        }
    }
}