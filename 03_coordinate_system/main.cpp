#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#include <iostream>
using namespace std;

int main()
{
    int w, h, c;

    unsigned char *img =
        stbi_load("../images/input.jpg", &w, &h, &c, 3);

    if (img == nullptr)
    {
        cout << "Image not loaded!" << endl;
        return 1;
    }

    cout << "Image size: "
         << w << " x " << h << endl;

    // Selected image coordinates
    int points[][2] =
    {
        {0, 0},
        {1000, 500},
        {2000, 1000},
        {3000, 2000},
        {w - 1, h - 1}
    };

    int n = 5;

    cout << "\nCoordinate comparison\n";
    cout << "---------------------\n";

    for(int k = 0; k < n; k++)
    {
        int x = points[k][0];
        int y = points[k][1];

        int yc = (h - 1) - y;

        cout << "P" << k + 1 << endl;

        cout << "Image      : ("
             << x << ", "
             << y << ")" << endl;

        cout << "Cartesian  : ("
             << x << ", "
             << yc << ")" << endl;

        cout << endl;
    }

    // Draw points on a copy of the image
    int size = w * h * 3;

    unsigned char *out = new unsigned char[size];

    for(int i = 0; i < size; i++)
        out[i] = img[i];

    // Make selected pixels white
    for(int k = 0; k < n; k++)
    {
        int x = points[k][0];
        int y = points[k][1];

        for(int dy = -5; dy <= 5; dy++)
        {
            for(int dx = -5; dx <= 5; dx++)
            {
                int nx = x + dx;
                int ny = y + dy;

                if(nx >= 0 && nx < w &&
                   ny >= 0 && ny < h)
                {
                    int i = (ny * w + nx) * 3;

                    out[i]     = 255;
                    out[i + 1] = 255;
                    out[i + 2] = 255;
                }
            }
        }
    }

    stbi_write_png(
        "../images/outputs/coordinates.png",
        w, h, 3, out, w * 3
    );

    cout << "Coordinate image saved.\n";

    delete[] out;

    stbi_image_free(img);

    return 0;
}