#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#include <iostream>
#include <fstream>
using namespace std;

void makeGray(
    unsigned char *img,
    unsigned char *gray,
    int w,
    int h)
{
    for(int y = 0; y < h; y++)
    {
        for(int x = 0; x < w; x++)
        {
            int i = (y * w + x) * 3;
            int j = y * w + x;

            int g =
                (int)(
                    0.299 * img[i] +
                    0.587 * img[i + 1] +
                    0.114 * img[i + 2]
                );

            gray[j] = (unsigned char)g;
        }
    }
}

void histogram(
    unsigned char *img,
    int w,
    int h,
    int hist[256])
{
    for(int i = 0; i < 256; i++)
        hist[i] = 0;

    int n = w * h;

    for(int i = 0; i < n; i++)
    {
        int p = img[i];

        hist[p]++;
    }
}

void saveHistogram(
    int hist[256],
    const char *name)
{
    ofstream file(name);

    for(int i = 0; i < 256; i++)
    {
        file << i << " "
             << hist[i] << "\n";
    }

    file.close();
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

    unsigned char *dark =
        new unsigned char[n];

    unsigned char *bright =
        new unsigned char[n];

    unsigned char *low =
        new unsigned char[n];

    // --------------------------------
    // RGB -> grayscale
    // --------------------------------

    makeGray(
        img,
        gray,
        w,
        h
    );

    // --------------------------------
    // Create dark, bright and
    // low-contrast versions
    // --------------------------------

    for(int i = 0; i < n; i++)
    {
        // Dark image
        dark[i] =
            (unsigned char)(
                gray[i] * 0.5
            );

        // Bright image
        int b =
            gray[i] + 80;

        if(b > 255)
            b = 255;

        bright[i] =
            (unsigned char)b;

        // Low contrast image
        low[i] =
            (unsigned char)(
                80 +
                gray[i] * 0.4
            );
    }

    // --------------------------------
    // Histograms
    // --------------------------------

    int h1[256];
    int h2[256];
    int h3[256];
    int h4[256];

    histogram(
        gray,
        w,
        h,
        h1
    );

    histogram(
        dark,
        w,
        h,
        h2
    );

    histogram(
        bright,
        w,
        h,
        h3
    );

    histogram(
        low,
        w,
        h,
        h4
    );

    // --------------------------------
    // Save images
    // --------------------------------

    stbi_write_png(
        "../images/outputs/hist_gray.png",
        w,
        h,
        1,
        gray,
        w
    );

    stbi_write_png(
        "../images/outputs/hist_dark.png",
        w,
        h,
        1,
        dark,
        w
    );

    stbi_write_png(
        "../images/outputs/hist_bright.png",
        w,
        h,
        1,
        bright,
        w
    );

    stbi_write_png(
        "../images/outputs/hist_low.png",
        w,
        h,
        1,
        low,
        w
    );

    // --------------------------------
    // Save histogram data
    // --------------------------------

    saveHistogram(
        h1,
        "../images/outputs/hist_gray.txt"
    );

    saveHistogram(
        h2,
        "../images/outputs/hist_dark.txt"
    );

    saveHistogram(
        h3,
        "../images/outputs/hist_bright.txt"
    );

    saveHistogram(
        h4,
        "../images/outputs/hist_low.txt"
    );

    cout << "\nHistogram calculation completed."
         << endl;

    cout << "Histogram data saved." << endl;

    delete[] gray;
    delete[] dark;
    delete[] bright;
    delete[] low;

    stbi_image_free(img);

    return 0;
}