#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int W = 800;
const int H = 600;

struct Point3D
{
    double x;
    double y;
    double z;
};

struct Point2D
{
    int x;
    int y;
};

int main()
{
    cout << "Experiment 10" << endl;
    cout << "From Scene to Digital Image" << endl;

    // ------------------------------------------------
    // STEP 1: Create a simple 3D scene
    // ------------------------------------------------

    Point3D scene[] =
        {
            {-2.0, -1.5, 6.0},
            {-1.0, 1.0, 5.0},
            {0.0, 0.0, 4.0},
            {1.5, 1.0, 5.0},
            {2.0, -1.0, 6.0},
            {0.0, -1.5, 7.0}};

    int n = 6;

    cout << "\n3D Scene Points:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1
             << " = ("
             << scene[i].x << ", "
             << scene[i].y << ", "
             << scene[i].z << ")"
             << endl;
    }

    // ------------------------------------------------
    // STEP 2: Projection
    // ------------------------------------------------

    double f = 300.0;

    Point2D projected[6];

    cout << "\nProjection:\n";

    for (int i = 0; i < n; i++)
    {
        double xp =
            f * scene[i].x /
            scene[i].z;

        double yp =
            f * scene[i].y /
            scene[i].z;

        int px =
            (int)(xp + W / 2);

        int py =
            (int)(H / 2 - yp);

        projected[i].x = px;
        projected[i].y = py;

        cout << "P" << i + 1
             << " -> ("
             << px << ", "
             << py << ")"
             << endl;
    }

    // ------------------------------------------------
    // STEP 3: Sampling
    // ------------------------------------------------

    unsigned char image[H][W] = {};

    cout << "\nSampling..." << endl;

    for (int i = 0; i < n; i++)
    {
        int x = projected[i].x;
        int y = projected[i].y;

        if (x >= 0 && x < W &&
            y >= 0 && y < H)
        {
            image[y][x] = 255;
        }
    }

    // ------------------------------------------------
    // STEP 4: Quantization
    // ------------------------------------------------

    cout << "Quantization..." << endl;

    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            int p = image[y][x];

            // 4 intensity levels
            int q =
                (p / 64) * 64;

            if (q > 255)
                q = 255;

            image[y][x] =
                (unsigned char)q;
        }
    }

    // ------------------------------------------------
    // STEP 5: Simple image processing
    // ------------------------------------------------

    cout << "Image processing..." << endl;

    unsigned char processed[H][W] = {};

    for (int y = 1; y < H - 1; y++)
    {
        for (int x = 1; x < W - 1; x++)
        {
            int gx =
                -image[y - 1][x - 1] + image[y - 1][x + 1] - 2 * image[y][x - 1] + 2 * image[y][x + 1] - image[y + 1][x - 1] + image[y + 1][x + 1];

            int gy =
                -image[y - 1][x - 1] - 2 * image[y - 1][x] - image[y - 1][x + 1] + image[y + 1][x - 1] + 2 * image[y + 1][x] + image[y + 1][x + 1];

            int mag =
                abs(gx) + abs(gy);

            if (mag > 255)
                mag = 255;

            processed[y][x] =
                (unsigned char)mag;
        }
    }

    // ------------------------------------------------
    // STEP 6: Save digital image
    // ------------------------------------------------

    ofstream file(
        "../images/outputs/scene_image.pgm");

    file << "P2\n";
    file << W << " " << H << "\n";
    file << "255\n";

    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            file << (int)image[y][x];

            if (x != W - 1)
                file << " ";
        }

        file << "\n";
    }

    file.close();

    // ------------------------------------------------
    // STEP 7: Save processed image
    // ------------------------------------------------

    ofstream file2(
        "../images/outputs/scene_processed.pgm");

    file2 << "P2\n";
    file2 << W << " " << H << "\n";
    file2 << "255\n";

    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            file2 << (int)processed[y][x];

            if (x != W - 1)
                file2 << " ";
        }

        file2 << "\n";
    }

    file2.close();

    cout << "\nPipeline completed." << endl;

    cout << "\n3D Scene" << endl;
    cout << "   ↓" << endl;
    cout << "Projection" << endl;
    cout << "   ↓" << endl;
    cout << "Sampling" << endl;
    cout << "   ↓" << endl;
    cout << "Quantization" << endl;
    cout << "   ↓" << endl;
    cout << "Digital Image" << endl;
    cout << "   ↓" << endl;
    cout << "Image Processing" << endl;
    cout << "   ↓" << endl;
    cout << "Visual Information" << endl;

    return 0;
}