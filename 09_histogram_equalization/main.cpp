#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#include <iostream>
#include <fstream>
using namespace std;

void calculateHistogram(
    unsigned char *img,
    int n,
    int hist[256])
{
    for(int i = 0; i < 256; i++)
        hist[i] = 0;

    for(int i = 0; i < n; i++)
    {
        hist[img[i]]++;
    }
}

int main()
{
    int w, h, c;

    unsigned char *img =
        stbi_load(
            "../images/outputs/hist_low.png",
            &w,
            &h,
            &c,
            1
        );

    if(img == nullptr)
    {
        cout << "Low contrast image not loaded!"
             << endl;

        return 1;
    }

    cout << "Low contrast image loaded."
         << endl;

    int n = w * h;

    // -------------------------------------
    // Step 1: Histogram
    // -------------------------------------

    int hist[256];

    calculateHistogram(
        img,
        n,
        hist
    );

    // -------------------------------------
    // Step 2: CDF
    // -------------------------------------

    int cdf[256];

    cdf[0] = hist[0];

    for(int i = 1; i < 256; i++)
    {
        cdf[i] =
            cdf[i - 1] +
            hist[i];
    }

    // -------------------------------------
    // Step 3: Find minimum non-zero CDF
    // -------------------------------------

    int cdfMin = 0;

    for(int i = 0; i < 256; i++)
    {
        if(cdf[i] != 0)
        {
            cdfMin = cdf[i];
            break;
        }
    }

    cout << "CDF minimum = "
         << cdfMin << endl;

    // -------------------------------------
    // Step 4: Create mapping
    // -------------------------------------

    unsigned char map[256];

    for(int i = 0; i < 256; i++)
    {
        if(n == cdfMin)
        {
            map[i] = 0;
        }
        else
        {
            double value =
                ((double)(cdf[i] - cdfMin) /
                 (double)(n - cdfMin))
                * 255.0;

            if(value < 0)
                value = 0;

            if(value > 255)
                value = 255;

            map[i] =
                (unsigned char)(value + 0.5);
        }
    }

    // -------------------------------------
    // Step 5: Apply mapping
    // -------------------------------------

    unsigned char *equalized =
        new unsigned char[n];

    for(int i = 0; i < n; i++)
    {
        equalized[i] =
            map[img[i]];
    }

    // -------------------------------------
    // Step 6: Save equalized image
    // -------------------------------------

    stbi_write_png(
        "../images/outputs/equalized.png",
        w,
        h,
        1,
        equalized,
        w
    );

    // -------------------------------------
    // Step 7: Calculate equalized histogram
    // -------------------------------------

    int histEq[256];

    calculateHistogram(
        equalized,
        n,
        histEq
    );

    // -------------------------------------
    // Save histograms
    // -------------------------------------

    ofstream f1(
        "../images/outputs/equalization_original.txt"
    );

    ofstream f2(
        "../images/outputs/equalization_equalized.txt"
    );

    for(int i = 0; i < 256; i++)
    {
        f1 << i << " "
           << hist[i] << "\n";

        f2 << i << " "
           << histEq[i] << "\n";
    }

    f1.close();
    f2.close();

    cout << "Equalized image saved."
         << endl;

    cout << "Histograms saved."
         << endl;

    delete[] equalized;

    stbi_image_free(img);

    return 0;
}