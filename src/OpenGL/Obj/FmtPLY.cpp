#include <fstream>
#include <iostream>
#include <Core/OpenGL/Obj/FmtPLY.h>
#include <glad/glad.h>
#include <3rdParty/happy.h>
using namespace std;
using namespace LUNA;
using namespace KTKR;

KTKR::Ptr<FmtPLY> FmtPLY::create(const std::string filePath)
{

    happly::PLYData plyIn{filePath};

    const size_t count = plyIn.getElement("vertex").count;
    auto pos = plyIn.getVertexPositions();

    std::vector<std::array<unsigned char, 3>> col;
    bool has_col = true;
    try
    {
        col = plyIn.getVertexColors();
    }
    catch (runtime_error e)
    {
        has_col = false;
    }
    vector<PLYVert> data(count);
    for (size_t i = 0; i < count; i++)
    {
        data[i].x = pos[i][0];
        data[i].y = pos[i][1];
        data[i].z = pos[i][2];
        data[i].w = 1.0;

        data[i].nx = 0;
        data[i].ny = 0;
        data[i].nz = 0;
        if (has_col)
        {
            data[i].r = col[i][0];
            data[i].g = col[i][1];
            data[i].b = col[i][2];
            data[i].a = 255ui8;
        }
        else
        {
            data[i].r = data[i].g = data[i].b = data[i].a = 255ui8;
        }
        data[i].u = 0;
        data[i].v = 0;
    }

    return std::make_shared<FmtPLY>(data, filePath);
}

FmtPLY::FmtPLY(std::vector<PLYVert> data, const std::string &filePath) : filePath{filePath}, VAO{}
{
    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(PLYVert), data.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_DOUBLE, GL_FALSE, // x,y,z,w
                          sizeof(PLYVert),
                          (void *)(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, // nx,ny,nz
                          sizeof(PLYVert),
                          (void *)(32));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, // r,g,b,a
                          sizeof(PLYVert),
                          (void *)(56));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_DOUBLE, GL_FALSE, // u,v
                          sizeof(PLYVert),
                          (void *)(64));
    glBindVertexArray(0);
    attrNum = 4;
    pointNum = data.size();
    hasIndex = false;
    isValid = true;
    mode = GL_POINTS;
}

#ifdef DEPRECATED_FEATURE
KTKR::Ptr<FmtPLY> FmtPLY::_create(const std::string filePath)
{

    ifstream fopen;

    if (!filePath.empty())
        fopen.open(filePath, ios::in);
    else
        return nullptr;
    if (!fopen.is_open())
    {
        cerr << "Failed to load file: " << filePath << endl;
        return nullptr;
    }

    // =================================================
    // Porperties
    size_t vertexNum, faceNum;
    vector<GLenum> propertyType;
    vector<GLenum> elementType;
    vector<GLsizei> count;         /*number of properties each element contains*/
    vector<GLvoid *> elementArray; /*save information of vertex,different element in different array*/
    GLuint *indices;               /*index of face,indicate the index of vertex that each face contains*/
    bool enableEBO = false;

    struct PLYVert
    {
        float x, y, z, w;
        float nx, ny, nz;
        float r, g, b, a;
        float u, v;
    };
    vector<bool> mask{
        {
            0, 0, 0, 0, // x y z w
            0, 0, 0,    // nx ny nz
            0, 0, 0, 0, // r g b a
            0, 0        // u v
        }};
    vector<PLYVert> vertData;
    // =================================================
    // Header

    string filein;
    while (!fopen.eof())
    {
        fopen >> filein;
        if (filein == "ply" || filein == "PLY")
        { // this is the header of .ply file
        }
        else if (filein == "comment")
        { // this is the comment
            getline(fopen, filein, '\n');
        }
        else if (filein == "format")
        { // this is the format information
            getline(fopen, filein, '\n');
        }
        else if (filein == "element")
        { // element information, only accept vertex and face. ignore user-defined element
            fopen >> filein;
            if (filein == "vertex")
            { // read the number of vertex
                fopen >> vertexNum;
                vertData.resize(vertexNum);
            }
            else if (filein == "face")
            { // read the number of face
                enableEBO = true;
                fopen >> faceNum;
                //ignore this and the next lines
                getline(fopen, filein, '\n');
                getline(fopen, filein, '\n');
            }
            else
            { // user-defined element
                cerr << "ignore user-defined element!" << endl;
                getline(fopen, filein, '\n');
            }
        }
        else if (filein == "property")
        {                    //property,only accept xyz/nxyz/rgb
            fopen >> filein; //read in type of element
            if (filein == "char" || filein == "int8")
            {
                propertyType.push_back(GL_BYTE);
            }
            else if (filein == "uchar" || filein == "uint8")
            {
                propertyType.push_back(GL_UNSIGNED_BYTE);
            }
            else if (filein == "short" || filein == "int16")
            {
                propertyType.push_back(GL_SHORT);
            }
            else if (filein == "ushort" || filein == "uint16")
            {
                propertyType.push_back(GL_UNSIGNED_SHORT);
            }
            else if (filein == "int" || filein == "int32")
            {
                propertyType.push_back(GL_INT);
            }
            else if (filein == "uint" || filein == "uint32")
            {
                propertyType.push_back(GL_UNSIGNED_INT);
            }
            else if (filein == "float" || filein == "float32")
            {
                propertyType.push_back(GL_FLOAT);
            }
            else if (filein == "double" || filein == "float64")
            {
                propertyType.push_back(GL_DOUBLE);
            }
            else
            { // use GLdouble as default
                cerr << "Undefined property type." << endl;
                propertyType.push_back(GL_DOUBLE);
            }
            fopen >> filein;
            if (filein == "x")
            {
                elementType.push_back(GL_VERTEX_ARRAY);
                getline(fopen, filein, '\n'); // x
                getline(fopen, filein, '\n'); // y
                count.push_back(2);
                mask[0] = mask[1] = 1;
            }
            else if (filein == "nx")
            {
                elementType.push_back(GL_NORMAL_ARRAY);
                getline(fopen, filein, '\n'); // nx
                getline(fopen, filein, '\n'); // ny
                getline(fopen, filein, '\n'); // nz
                count.push_back(3);
                mask[4] = mask[5] = mask[6] = 1;
            }
            else if (filein == "red")
            {
                elementType.push_back(GL_COLOR_ARRAY);
                getline(fopen, filein, '\n'); // red
                getline(fopen, filein, '\n'); // green
                getline(fopen, filein, '\n'); // blue
                count.push_back(3);
                mask[7] = mask[8] = mask[9] = 1;
            }
            else if (filein == "z" || filein == "w")
            { // forth property
                count[count.size() - 1] += 1;
                propertyType.pop_back();
                mask[3] = 1;
            }
            else if (filein == "alpha")
            {
                count[count.size() - 1] += 1;
                propertyType.pop_back();
                mask[10] = 1;
            }
            else if (filein == "u" || filein == "s")
            {
                elementType.push_back(GL_TEXTURE_COORD_ARRAY);
                getline(fopen, filein, '\n'); // u s
                getline(fopen, filein, '\n'); // v t
                count.push_back(2);
                mask[11] = mask[12] = 1;
            }
            else
            {
                cerr << "Unknown property!" << endl;
                return nullptr;
            }
        }
        else if (filein == "end_header")
        { //header end
            // ckeck
            if (count.size() != propertyType.size() || count.size() != elementType.size())
            {
                cerr << "the number of element collision" << endl;
                return nullptr;
            }
            // start to read element information
            // initialise the elementArray
            GLvoid *subarray = NULL;
            for (int i = 0; i < propertyType.size(); i++)
            {
                switch (propertyType[i])
                {
                case GL_BYTE:
                    subarray = new GLbyte[vertexNum * count[i]];
                    elementArray.push_back(subarray);
                    break;
                case GL_UNSIGNED_BYTE:
                    subarray = new GLubyte[vertexNum * count[i]];
                    elementArray.push_back(subarray);
                    break;
                case GL_SHORT:
                    subarray = new GLshort[vertexNum * count[i]];
                    elementArray.push_back(subarray);
                    break;
                case GL_UNSIGNED_SHORT:
                    subarray = new GLushort[vertexNum * count[i]];
                    elementArray.push_back(subarray);
                    break;
                case GL_INT:
                    subarray = new GLint[vertexNum * count[i]];
                    elementArray.push_back(subarray);
                    break;
                case GL_UNSIGNED_INT:
                    subarray = new GLuint[vertexNum * count[i]];
                    elementArray.push_back(subarray);
                    break;
                case GL_FLOAT:
                    subarray = new GLfloat[vertexNum * count[i]];
                    elementArray.push_back(subarray);
                    break;
                case GL_DOUBLE:
                    subarray = new GLdouble[vertexNum * count[i]];
                    elementArray.push_back(subarray);
                    break;
                }
            }
            if (enableEBO)
                indices = new GLuint[faceNum * 3];

            // =================================================
            // read vertex information
            int totalelement = 0;
            for (int i = 0; i < count.size(); i++)
                totalelement += count[i];
            for (int i = 0; i < vertexNum; i++)
            {
                for (int j = 0; j < count.size(); j++)
                    for (int k = 0; k < count[j]; k++)
                    {
                        switch (propertyType[j])
                        {
                        case GL_BYTE:
                            GLdouble tem = 0; // (GLdouble)(((GLbyte*)(elementArray[j]))[i*count[j]+k]);
                            fopen >> tem;
                            ((GLbyte *)(elementArray[j]))[i * count[j] + k] = GLbyte(tem);
                            break;
                        case GL_UNSIGNED_BYTE:
                            GLint tem = 0; // (GLdouble)(((GLubyte*)(elementArray[j]))[i*count[j]+k]);
                            fopen >> tem;
                            ((GLubyte *)(elementArray[j]))[i * count[j] + k] = GLubyte(tem);
                            break;
                        case GL_SHORT:
                            fopen >> ((GLshort *)(elementArray[j]))[i * count[j] + k];
                            break;
                        case GL_UNSIGNED_SHORT:
                            fopen >> ((GLushort *)(elementArray[j]))[i * count[j] + k];
                            break;
                        case GL_INT:
                            fopen >> ((GLint *)(elementArray[j]))[i * count[j] + k];
                            break;
                        case GL_UNSIGNED_INT:
                            fopen >> ((GLuint *)(elementArray[j]))[i * count[j] + k];
                            break;
                        case GL_FLOAT:
                            fopen >> ((GLfloat *)(elementArray[j]))[i * count[j] + k];
                            break;
                        case GL_DOUBLE:
                            fopen >> ((GLdouble *)(elementArray[j]))[i * count[j] + k];
                            break;
                        }
                    }
            }
            // read face information
            int front = 0, i = 0;

            fopen >> front;
            while (front == 3 && i < faceNum)
            {
                fopen >> indices[i * 3] >> indices[i * 3 + 1] >> indices[i * 3 + 2];
                fopen >> front;
                i++;
            }
        }
        else
        {
            continue;
        }
    }
    fopen.close();
    // =================================================
    // Generate VBO

    return nullptr;
}
#endif