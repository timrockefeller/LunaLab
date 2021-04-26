#include <Core/OpenGL/VAO.h>
#include <glad/glad.h>

using namespace std;
using namespace LUNA;
using namespace KTKR;
VAO::VAO(void const *data,
         size_t dataSize,
         const vector<unsigned int> &attrLen)
{
    if (data == NULL || dataSize == 0 || attrLen.size() == 0)
    {
        isValid = false;
        ID = 0;
        return;
    }
    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    unsigned int patchLen = 0;
    for (auto &len : attrLen)
        patchLen += len;
    for (unsigned int i = 0, cur = 0; i < attrLen.size(); i++)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, attrLen[i], GL_FLOAT, GL_FALSE,
                              patchLen * sizeof(float),
                              (void *)(cur * sizeof(float)));
        cur += attrLen[i];
    }
    glBindVertexArray(0);
    attrNum = attrLen.size();
    pointNum = dataSize / (sizeof(float) * patchLen);
    hasIndex = false;
    isValid = true;
    mode = GL_TRIANGLES;
}

VAO::VAO(KTKR::AlignedChunk data,
         const vector<unsigned int> &attrLen)
{
    bool valid = true;
    if (!data.IsValid() || data.size() == 0 || attrLen.size() == 0)
        valid = false;

    // check each ele in attr matchs length
    for (unsigned int i = 0, curattr = 0; i < attrLen.size(); i++)
    {
        size_t check = data.layout.lengths[curattr];
        for (size_t j = 1; j < attrLen[i]; j++)
            if (check != data.layout.lengths[curattr + j])
            {
                valid = false;
                break;
            }
        if (!valid)
            break;
        curattr += attrLen[i];
    }

    if (!valid)
    {
        isValid = false;
        ID = 0;
        return;
    }

    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * data.layout.capacity, data.Data(), GL_STATIC_DRAW);

    for (unsigned int i = 0, curattr = 0, curbyte = 0; i < attrLen.size(); i++)
    {

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, attrLen[i], GL_FLOAT, // TODO dynamic length of type
                              GL_FALSE,
                              data.layout.capacity,
                              (void *)(curbyte));
        curattr += attrLen[i];
        curbyte += attrLen[i] * data.layout.lengths[curattr];
    }
    glBindVertexArray(0);
}

VAO::VAO(void const *data,
         unsigned int dataSize,
         const vector<unsigned int> &attrLen,
         unsigned int const *index,
         unsigned int indexSize)
    : VAO(data, dataSize, attrLen)
{
    isValid = GenBindEBO(index, indexSize);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &ID);
    if (hasIndex)
        glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
}

bool VAO::GenBindEBO(unsigned int const *index, unsigned int indexSize)
{
    Use();
    if (index == NULL || indexSize <= 0)
        return false;
    hasIndex = true;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, index, GL_STATIC_DRAW);
    pointNum = indexSize / sizeof(size_t);
    return true;
}

unsigned int VAO::GetID() const
{
    return ID;
}
unsigned int VAO::GetAttrNum() const
{
    return attrNum;
}
bool VAO::IsValid() const
{
    return isValid;
}
bool VAO::Use() const
{
    if (!IsValid())
    {
        return false;
    }
    glBindVertexArray(ID);
    return true;
}
bool VAO::Draw() const
{
    if (!Use())
        return false;

    if (hasIndex)
        glDrawElements(mode, pointNum, GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(mode, 0, pointNum);
    glBindVertexArray(0);
    return true;
}
void VAO::SetRenderMode(unsigned int _mode)
{
    mode = _mode;
}