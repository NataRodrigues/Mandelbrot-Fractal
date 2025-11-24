

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITER 500
#define WIDTH 800
#define HEIGHT 600

int main(void)
{
    FILE *fp = fopen("mandelbrot_puro.ppm", "wb");
    if (!fp)
    {
        perror("Erro ao criar o arquivo");
        return 1;
    }

    fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);

    
    unsigned char palette[16][3] = {
        {66, 30, 15}, {25, 7, 26}, {9, 1, 47}, {4, 4, 73}, {0, 7, 100}, {12, 44, 138}, {24, 82, 177}, {57, 125, 209}, {134, 181, 229}, {211, 236, 248}, {241, 233, 191}, {248, 201, 95}, {255, 170, 0}, {204, 128, 0}, {153, 87, 0}, {106, 52, 3}};

    
    double xMin = -2.5, xMax = 1.0;
    double yMin = -1.2, yMax = 1.2;

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            double cx = xMin + (xMax - xMin) * x / WIDTH;
            double cy = yMin + (yMax - yMin) * y / HEIGHT;

            double zx = 0.0, zy = 0.0;
            int iter = 0;

            while (zx * zx + zy * zy < 4.0 && iter < MAX_ITER)
            {
                double tmp = zx * zx - zy * zy + cx;
                zy = 2.0 * zx * zy + cy;
                zx = tmp;
                iter++;
            }

            unsigned char color[3];
            if (iter == MAX_ITER)
            {
                color[0] = color[1] = color[2] = 0; 
            }
            else
            {
                unsigned char *p = palette[iter % 16];
                color[0] = p[0];
                color[1] = p[1];
                color[2] = p[2];
            }

            fwrite(color, 1, 3, fp);
        }
    }

    fclose(fp);
    printf("Imagem gerada: mandelbrot_puro.ppm\n");
    return 0;
}
