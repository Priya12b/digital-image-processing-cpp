#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#include <iostream>
#include <algorithm>

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

    cout << "Image loaded successfully\n\n";

    cout << "Width    : " << w << endl;
    cout << "Height   : " << h << endl;
    cout << "Channels : 3" << endl;
    cout << "Data type: unsigned char" << endl;

    int n = w * h;

    unsigned char *R = new unsigned char[n];
    unsigned char *G = new unsigned char[n];
    unsigned char *B = new unsigned char[n];

    int rmin = 255, rmax = 0;
    int gmin = 255, gmax = 0;
    int bmin = 255, bmax = 0;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int i = (y * w + x) * 3;
            int j = y * w + x;

            R[j] = img[i];
            G[j] = img[i + 1];
            B[j] = img[i + 2];

            rmin = min(rmin, (int)R[j]);
            rmax = max(rmax, (int)R[j]);

            gmin = min(gmin, (int)G[j]);
            gmax = max(gmax, (int)G[j]);

            bmin = min(bmin, (int)B[j]);
            bmax = max(bmax, (int)B[j]);
        }
    }

    cout << "\nIntensity ranges:\n";

    cout << "R : " << rmin << " - " << rmax << endl;
    cout << "G : " << gmin << " - " << gmax << endl;
    cout << "B : " << bmin << " - " << bmax << endl;

    stbi_write_png(
        "../images/outputs/red.png",
        w, h, 1, R, w
    );

    stbi_write_png(
        "../images/outputs/green.png",
        w, h, 1, G, w
    );

    stbi_write_png(
        "../images/outputs/blue.png",
        w, h, 1, B, w
    );

    cout << "\nChannel images saved successfully." << endl;

    delete[] R;
    delete[] G;
    delete[] B;

    stbi_image_free(img);

    return 0;
}