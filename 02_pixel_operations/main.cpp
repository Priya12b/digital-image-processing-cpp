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

    cout << "Image Loaded\n";

    int n = w * h;

    unsigned char *gray = new unsigned char[n];
    unsigned char *neg = new unsigned char[n];
    unsigned char *bright = new unsigned char[n];
    unsigned char *contrast = new unsigned char[n];
    unsigned char *thresh = new unsigned char[n];

    int mn = 255;
    int mx = 0;

    // RGB -> Gray
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int i = (y * w + x) * 3;
            int j = y * w + x;

            int g =
                0.299 * img[i] +
                0.587 * img[i + 1] +
                0.114 * img[i + 2];

            gray[j] = g;

            if (g < mn)
                mn = g;

            if (g > mx)
                mx = g;
        }
    }

    cout << "Gray min = " << mn << endl;
    cout << "Gray max = " << mx << endl;

    // Operations
    for (int i = 0; i < n; i++)
    {
        // Negative
        neg[i] = 255 - gray[i];

        // Brightness
        int b = gray[i] + 40;

        if (b > 255)
            b = 255;

        bright[i] = b;

        // Contrast
        contrast[i] =
            (gray[i] - mn) * 255 / (mx - mn);

        // Threshold
        if (gray[i] >= 128)
            thresh[i] = 255;
        else
            thresh[i] = 0;
    }

    // Save
    stbi_write_png(
        "../images/outputs/gray.png",
        w, h, 1, gray, w);

    stbi_write_png(
        "../images/outputs/negative.png",
        w, h, 1, neg, w);

    stbi_write_png(
        "../images/outputs/brightness.png",
        w, h, 1, bright, w);

    stbi_write_png(
        "../images/outputs/contrast.png",
        w, h, 1, contrast, w);

    stbi_write_png(
        "../images/outputs/threshold.png",
        w, h, 1, thresh, w);

    cout << "\nImages Saved\n";

    delete[] gray;
    delete[] neg;
    delete[] bright;
    delete[] contrast;
    delete[] thresh;

    stbi_image_free(img);

    return 0;
}