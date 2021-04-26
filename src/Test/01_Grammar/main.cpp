#include <iostream>
#include <Common/AlignedChunk.h>
using namespace std;
using namespace KTKR;

struct PLYVert
{
    double x, y, z, w;
    double nx, ny, nz;
    unsigned char r, g, b, a;
    double u, v;
};

int main()
{
    AlignedChunk c{
        {sizeof(double), sizeof(double), sizeof(double), sizeof(double),
         sizeof(double), sizeof(double), sizeof(double),
         sizeof(unsigned char), sizeof(unsigned char), sizeof(unsigned char), sizeof(unsigned char),
         sizeof(double), sizeof(double)},
        2};

    sizeof(PLYVert);
    return 0;
}