#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#include <iostream>
using namespace std;

void sampleImage(
    unsigned char *img,
    int w,
    int h,
    int factor,
    const char *name)
{
    int nw = w / factor;
    int nh = h / factor;

    unsigned char *out =
        new unsigned char[nw * nh * 3];

    for(int y = 0; y < nh; y++)
    {
        for(int x = 0; x < nw; x++)
        {
            // Take every factor-th pixel
            int srcX = x * factor;
            int srcY = y * factor;

            int src = (srcY * w + srcX) * 3;
            int dst = (y * nw + x) * 3;

            out[dst]     = img[src];
            out[dst + 1] = img[src + 1];
            out[dst + 2] = img[src + 2];
        }
    }

    stbi_write_png(
        name,
        nw,
        nh,
        3,
        out,
        nw * 3
    );

    cout << "Factor " << factor << endl;
    cout << "Output size: "
         << nw << " x " << nh << endl;

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

    cout << "Original image: "
         << w << " x " << h << endl;

    cout << "\nSampling...\n\n";

    sampleImage(
        img,
        w,
        h,
        2,
        "../images/outputs/sampling_2.png"
    );

    cout << endl;

    sampleImage(
        img,
        w,
        h,
        4,
        "../images/outputs/sampling_4.png"
    );

    cout << endl;

    sampleImage(
        img,
        w,
        h,
        8,
        "../images/outputs/sampling_8.png"
    );

    cout << "\nSampling completed." << endl;

    stbi_image_free(img);

    return 0;
}