#pragma once
#include <vector>

namespace LUNA
{
    class VAO
    {
    public:
        VAO() = default;
        VAO(unsigned int ID, unsigned int num)
            : ID(ID), isValid(true), pointNum(num) {}
        VAO(void const *data,
            size_t dataSize,
            const std::vector<unsigned int> &attrLen);
        VAO(void const *data,
            unsigned int dataSize,
            const std::vector<unsigned int> &attrLen,
            unsigned int const *index,
            unsigned int indexSize);
        ~VAO();

        unsigned int GetID() const;
        unsigned int GetAttrNum() const;
        bool IsValid() const;
        bool Use() const;
        bool Draw() const;
        void SetRenderMode(unsigned int);

    private:
        bool GenBindEBO(unsigned int const *index, unsigned int indexSize);
        //------------
        unsigned int attrNum;
        unsigned int ID;
        unsigned int VBO;
        unsigned int EBO;
        unsigned int pointNum;
        unsigned int mode;
        bool hasIndex;
        bool isValid;
    };
} // namespace LOGL
