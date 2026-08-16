#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#include <iostream>
#include <cmath>

using namespace std;

void quantize(
    unsigned char *gray,
    int w,
    int h,
    int levels,
    const char *name)
{
    int n = w * h;

    unsigned char *out =
        new unsigned char[n];

    for(int i = 0; i < n; i++)
    {
        int p = gray[i];

        int q =
            (int)round(
                p * (levels - 1) / 255.0
            );

        int v =
            (int)round(
                q * 255.0 / (levels - 1)
            );

        out[i] = (unsigned char)v;
    }

    stbi_write_png(
        name,
        w,
        h,
        1,
        out,
        w
    );

    cout << "Levels: "
         << levels << endl;

    delete[] out;
}

int main()
{
    int w, h, c;

    unsigned char *img =
        stbi_load(
            "../images/input.jpg",
            &w,
            &h,
            &c,
            3
        );

    if(img == nullptr)
    {
        cout << "Image not loaded!" << endl;
        return 1;
    }

    cout << "Image loaded." << endl;

    int n = w * h;

    unsigned char *gray =
        new unsigned char[n];

    // RGB -> grayscale
    for(int y = 0; y < h; y++)
    {
        for(int x = 0; x < w; x++)
        {
            int i =
                (y * w + x) * 3;

            int j =
                y * w + x;

            int g =
                (int)(
                    0.299 * img[i] +
                    0.587 * img[i + 1] +
                    0.114 * img[i + 2]
                );

            gray[j] =
                (unsigned char)g;
        }
    }

    cout << "\nQuantization results:\n\n";

    quantize(
        gray,
        w,
        h,
        128,
        "../images/outputs/quant_128.png"
    );

    quantize(
        gray,
        w,
        h,
        64,
        "../images/outputs/quant_64.png"
    );

    quantize(
        gray,
        w,
        h,
        16,
        "../images/outputs/quant_16.png"
    );

    quantize(
        gray,
        w,
        h,
        4,
        "../images/outputs/quant_4.png"
    );

    quantize(
        gray,
        w,
        h,
        2,
        "../images/outputs/quant_2.png"
    );

    cout << "\nQuantization completed." << endl;

    delete[] gray;

    stbi_image_free(img);

    return 0;
}