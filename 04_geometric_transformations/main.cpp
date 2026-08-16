#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#include <iostream>
#include <cmath>
using namespace std;

void setPixel(
    unsigned char *out,
    int w,
    int h,
    int x,
    int y,
    unsigned char r,
    unsigned char g,
    unsigned char b)
{
    if (x >= 0 && x < w && y >= 0 && y < h)
    {
        int i = (y * w + x) * 3;

        out[i] = r;
        out[i + 1] = g;
        out[i + 2] = b;
    }
}

int main()
{
    int w, h, c;

    unsigned char *img =
        stbi_load("../images/input.jpg",
                  &w, &h, &c, 3);

    if (img == nullptr)
    {
        cout << "Image not loaded!" << endl;
        return 1;
    }

    cout << "Image size: "
         << w << " x " << h << endl;

    int size = w * h * 3;

    // ------------------------------------------------
    // 1. TRANSLATION
    // ------------------------------------------------

    unsigned char *trans =
        new unsigned char[size];

    for (int i = 0; i < size; i++)
        trans[i] = 0;

    int tx = 200;
    int ty = 150;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int nx = x + tx;
            int ny = y + ty;

            if (nx >= 0 && nx < w &&
                ny >= 0 && ny < h)
            {
                int src = (y * w + x) * 3;
                int dst = (ny * w + nx) * 3;

                trans[dst] = img[src];
                trans[dst + 1] = img[src + 1];
                trans[dst + 2] = img[src + 2];
            }
        }
    }

    stbi_write_png(
        "../images/outputs/translation.png",
        w, h, 3, trans, w * 3);

    // ------------------------------------------------
    // 2. SCALING
    // ------------------------------------------------

    double sx = 0.5;
    double sy = 0.5;

    int sw = (int)(w * sx);
    int sh = (int)(h * sy);

    unsigned char *scale =
        new unsigned char[sw * sh * 3];

    for (int i = 0; i < sw * sh * 3; i++)
        scale[i] = 0;

    for (int y = 0; y < sh; y++)
    {
        for (int x = 0; x < sw; x++)
        {
            int srcX = (int)(x / sx);
            int srcY = (int)(y / sy);

            if (srcX < w && srcY < h)
            {
                int src = (srcY * w + srcX) * 3;
                int dst = (y * sw + x) * 3;

                scale[dst] = img[src];
                scale[dst + 1] = img[src + 1];
                scale[dst + 2] = img[src + 2];
            }
        }
    }

    stbi_write_png(
        "../images/outputs/scaling.png",
        sw, sh, 3, scale, sw * 3);

    // ------------------------------------------------
    // 3. ROTATION
    // ------------------------------------------------

    unsigned char *rot =
        new unsigned char[size];

    for (int i = 0; i < size; i++)
        rot[i] = 0;

    double angle = 30.0;

    double rad =
        angle * 3.141592653589793 / 180.0;

    double cs = cos(rad);
    double sn = sin(rad);

    double cx = (w - 1) / 2.0;
    double cy = (h - 1) / 2.0;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            double nx =
                cx +
                (x - cx) * cs -
                (y - cy) * sn;

            double ny =
                cy +
                (x - cx) * sn +
                (y - cy) * cs;

            int ix = (int)round(nx);
            int iy = (int)round(ny);

            if (ix >= 0 && ix < w &&
                iy >= 0 && iy < h)
            {
                int src = (y * w + x) * 3;
                int dst = (iy * w + ix) * 3;

                rot[dst] = img[src];
                rot[dst + 1] = img[src + 1];
                rot[dst + 2] = img[src + 2];
            }
        }
    }

    stbi_write_png(
        "../images/outputs/rotation.png",
        w, h, 3, rot, w * 3);

    // ------------------------------------------------
    // 4. REFLECTION
    // ------------------------------------------------

    unsigned char *ref =
        new unsigned char[size];

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int nx = w - 1 - x;

            int src = (y * w + x) * 3;
            int dst = (y * w + nx) * 3;

            ref[dst] = img[src];
            ref[dst + 1] = img[src + 1];
            ref[dst + 2] = img[src + 2];
        }
    }

    stbi_write_png(
        "../images/outputs/reflection.png",
        w, h, 3, ref, w * 3);

    cout << "\nTransformations completed.\n";

    cout << "\nTranslation:";
    cout << "\n(tx, ty) = ("
         << tx << ", " << ty << ")" << endl;

    cout << "\nScaling:";
    cout << "\n(sx, sy) = ("
         << sx << ", " << sy << ")" << endl;

    cout << "\nRotation:";
    cout << "\nAngle = "
         << angle << " degrees" << endl;

    cout << "\nReflection:";
    cout << "\nHorizontal reflection" << endl;

    delete[] trans;
    delete[] scale;
    delete[] rot;
    delete[] ref;

    stbi_image_free(img);

    return 0;
}