#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

unsigned char clampValue(double x)
{
    if(x < 0)
        return 0;

    if(x > 255)
        return 255;

    return (unsigned char)round(x);
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

    cout << "Image loaded successfully." << endl;

    int n = w * h;

    // ------------------------------------------
    // Output arrays
    // ------------------------------------------

    unsigned char *gray =
        new unsigned char[n];

    unsigned char *hue =
        new unsigned char[n];

    unsigned char *sat =
        new unsigned char[n];

    unsigned char *val =
        new unsigned char[n];

    unsigned char *Y =
        new unsigned char[n];

    unsigned char *Cb =
        new unsigned char[n];

    unsigned char *Cr =
        new unsigned char[n];

    // ------------------------------------------
    // Process every pixel
    // ------------------------------------------

    for(int y = 0; y < h; y++)
    {
        for(int x = 0; x < w; x++)
        {
            int i =
                (y * w + x) * 3;

            int j =
                y * w + x;

            double R = img[i];
            double G = img[i + 1];
            double B = img[i + 2];

            // ==================================
            // GRAYSCALE
            // ==================================

            double g =
                0.299 * R +
                0.587 * G +
                0.114 * B;

            gray[j] =
                clampValue(g);

            // ==================================
            // HSV
            // ==================================

            double r = R / 255.0;
            double gg = G / 255.0;
            double b = B / 255.0;

            double mx =
                max(r, max(gg, b));

            double mn =
                min(r, min(gg, b));

            double d =
                mx - mn;

            double H = 0;
            double S = 0;
            double V = mx;

            // Saturation
            if(mx != 0)
                S = d / mx;

            // Hue
            if(d == 0)
            {
                H = 0;
            }
            else if(mx == r)
            {
                H =
                    60.0 *
                    fmod(
                        ((gg - b) / d),
                        6.0
                    );

                if(H < 0)
                    H += 360.0;
            }
            else if(mx == gg)
            {
                H =
                    60.0 *
                    (((b - r) / d) + 2.0);
            }
            else
            {
                H =
                    60.0 *
                    (((r - gg) / d) + 4.0);
            }

            // Convert H from 0-360 to 0-255
            hue[j] =
                clampValue(
                    H * 255.0 / 360.0
                );

            sat[j] =
                clampValue(
                    S * 255.0
                );

            val[j] =
                clampValue(
                    V * 255.0
                );

            // ==================================
            // YCbCr
            // ==================================

            double yv =
                0.299 * R +
                0.587 * G +
                0.114 * B;

            double cb =
                -0.169 * R -
                0.331 * G +
                0.500 * B +
                128.0;

            double cr =
                0.500 * R -
                0.419 * G -
                0.081 * B +
                128.0;

            Y[j] =
                clampValue(yv);

            Cb[j] =
                clampValue(cb);

            Cr[j] =
                clampValue(cr);
        }
    }

    // ------------------------------------------
    // Save Grayscale
    // ------------------------------------------

    stbi_write_png(
        "../images/outputs/color_gray.png",
        w,
        h,
        1,
        gray,
        w
    );

    // ------------------------------------------
    // Save HSV
    // ------------------------------------------

    stbi_write_png(
        "../images/outputs/hue.png",
        w,
        h,
        1,
        hue,
        w
    );

    stbi_write_png(
        "../images/outputs/saturation.png",
        w,
        h,
        1,
        sat,
        w
    );

    stbi_write_png(
        "../images/outputs/value.png",
        w,
        h,
        1,
        val,
        w
    );

    // ------------------------------------------
    // Save YCbCr
    // ------------------------------------------

    stbi_write_png(
        "../images/outputs/y.png",
        w,
        h,
        1,
        Y,
        w
    );

    stbi_write_png(
        "../images/outputs/cb.png",
        w,
        h,
        1,
        Cb,
        w
    );

    stbi_write_png(
        "../images/outputs/cr.png",
        w,
        h,
        1,
        Cr,
        w
    );

    cout << "\nColor space conversion completed." << endl;

    cout << "\nOutputs created:" << endl;

    cout << "Grayscale" << endl;

    cout << "HSV:" << endl;
    cout << "  Hue" << endl;
    cout << "  Saturation" << endl;
    cout << "  Value" << endl;

    cout << "YCbCr:" << endl;
    cout << "  Y" << endl;
    cout << "  Cb" << endl;
    cout << "  Cr" << endl;

    delete[] gray;
    delete[] hue;
    delete[] sat;
    delete[] val;
    delete[] Y;
    delete[] Cb;
    delete[] Cr;

    stbi_image_free(img);

    return 0;
}