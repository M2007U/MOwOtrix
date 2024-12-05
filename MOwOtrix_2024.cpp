//version 2024.1114.1206

#pragma once

#include <iostream>
#include <iomanip>

#include <stdlib.h>
#include <cstdlib>

#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <cstring>
#include <cctype>

#include <cmath>
#include <math.h>

#include <typeinfo>
#include <sys/types.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "FOwOFunctions_2024.cpp"

using namespace std;

template <typename TYPE>
class MOwOtrix_Container
{
    public:

    int Width;
    int Height;
    int ElementCount;
    vector<TYPE> content;
    TYPE DataTypeIdentifier;

    FOwO fowo;

    MOwOtrix_Container(int InWidth, int InHeight, vector<TYPE> InContent)
    {
        Width = InWidth;
        Height = InHeight;
        ElementCount = Width * Height;
        DataTypeIdentifier = InContent[0];

        if (InContent.size() != ElementCount)
        {
            cout << fowo.cOwOut.ConsoleQuick("error","content length does not match with element count");
        }
        else
        {
            content = InContent;
        }
    }

    // Copy constructor
    MOwOtrix_Container(MOwOtrix_Container& other) : Width(other.Width), Height(other.Height), ElementCount(other.ElementCount), content(other.content), DataTypeIdentifier(other.DataTypeIdentifier), fowo(other.fowo) {}

    // Copy assignment operator (optional but recommended for copy semantics)
    MOwOtrix_Container& operator=(const MOwOtrix_Container& other) {
        if (this != &other)
        {
            Width = other.Width;
            Height = other.Height;
            ElementCount = other.ElementCount;
            content = other.content;
            DataTypeIdentifier = other.DataTypeIdentifier;
            fowo = other.fowo;
        }
        return *this;
    }

    string printContent(int InCellWidth, string paddingSubstring, char paddingAlign, string Label)
    {
        string ReturnResult = "";

        ReturnResult = ReturnResult + Label + " : \n";

        for(int i = 0 ; i < Height ; i++)
        {
            for(int j = 0 ; j < Width ; j++)
            {
                ReturnResult = ReturnResult + fowo.strOwOng.mOwOnip.padding(to_string(content[ i * Width + j ]),paddingSubstring,InCellWidth,paddingAlign) + " ";
            }
            ReturnResult = ReturnResult + "\n";
        }

        return ReturnResult;
    }

    void Zero()
    {
        ElementCount = Width * Height;
        content = {};

        for(int i = 0 ; i < ElementCount ; i++)
        {
            content.push_back(0);
        }

        return;
    }

    void Identity(int InSize)
    {
        Width = InSize;
        Height = InSize;
        ElementCount = Width * Height;
        content = {};

        for(int i = 0 ; i < Height ; i++)
        {
            for(int j = 0 ; j < Width ; j++)
            {
                if (i==j)
                {
                    content.push_back(1);
                }
                else
                {
                    content.push_back(0);
                }
            }
        }

        return;


    }
};

class MOwOtrix_Operation
{
    public:

    FOwO fowo;

    template <typename TYPE>
    bool MatrixIsValid (MOwOtrix_Container<TYPE> &MatrixA)
    {
        if (MatrixA.content.size() == 0)
        {
            cout << fowo.cOwOut.ConsoleQuick("error","content of the given matrix is empty") << endl;
            return false;
        }

        MatrixA.DataTypeIdentifier = MatrixA.content[0];
        if (!fowo.DatatypeOfVar_IsNumeric(MatrixA.DataTypeIdentifier))
        {
            cout << fowo.cOwOut.ConsoleQuick("error","datatype of the given matrix cannot be computed") << endl;
            return false;
        }

        MatrixA.ElementCount = MatrixA.Width * MatrixA.Height;
        if (MatrixA.content.size() != MatrixA.ElementCount)
        {
            cout << fowo.cOwOut.ConsoleQuick("error","dimension of the given matrix does ont fit with the content length") << endl;
            return false;
        }

        return true;
    }

    template <typename TYPE>
    void Addition (MOwOtrix_Container<TYPE> &MatrixA, MOwOtrix_Container<TYPE> &MatrixB, MOwOtrix_Container<TYPE> &MatrixO)
    {
        if (!MatrixIsValid(MatrixA) || !MatrixIsValid(MatrixB))
        {
            cout << fowo.cOwOut.ConsoleQuick("error","the given matrices cannot be computed");
            return;
        }

        if (MatrixA.Width == MatrixB.Width && MatrixA.Height == MatrixB.Height)
        {
            MatrixO.Width = MatrixA.Width;
            MatrixO.Height = MatrixA.Height;
            MatrixO.ElementCount = MatrixO.Width * MatrixO.Height;
            MatrixO.content = {};

            for(int i = 0 ; i < MatrixA.ElementCount ; i++)
            {
                MatrixO.content.push_back(MatrixA.content[i] + MatrixB.content[i]);
            }

            return ;
        }
        else
        {
            cout << fowo.cOwOut.ConsoleQuick("error","dimensions of given matrices does not match");
            return;
        }
    }

    template <typename TYPE>
    void Multiplication_Dot (MOwOtrix_Container<TYPE> &MatrixA, MOwOtrix_Container<TYPE> &MatrixB, MOwOtrix_Container<TYPE> &MatrixO)
    {
        if (!MatrixIsValid(MatrixA) || !MatrixIsValid(MatrixB))
        {
            cout << fowo.cOwOut.ConsoleQuick("error","the given matrices cannot be computed");
            return;
        }

        if (MatrixA.Width == MatrixB.Width && MatrixA.Height == MatrixB.Height)
        {
            MatrixO.Width = MatrixA.Width;
            MatrixO.Height = MatrixA.Height;
            MatrixO.ElementCount = MatrixO.Width * MatrixO.Height;
            MatrixO.content = {};

            for(int i = 0 ; i < MatrixA.ElementCount ; i++)
            {
                MatrixO.content.push_back(MatrixA.content[i] * MatrixB.content[i]);
            }

            return ;
        }
        else
        {
            cout << fowo.cOwOut.ConsoleQuick("error","dimensions of given matrices does not match");
            return;
        }
    }

    template <typename TYPE>
    void Multiplication_Matrix (MOwOtrix_Container<TYPE> &MatrixA, MOwOtrix_Container<TYPE> &MatrixB, MOwOtrix_Container<TYPE> &MatrixO)
    {
        if (!MatrixIsValid(MatrixA) || !MatrixIsValid(MatrixB))
        {
            cout << fowo.cOwOut.ConsoleQuick("error","the given matrices cannot be computed");
            return;
        }

        if (MatrixA.Width == MatrixB.Height)
        {
            MatrixO.Width = MatrixB.Width;
            MatrixO.Height = MatrixA.Height;
            MatrixO.ElementCount = MatrixO.Width * MatrixO.Height;
            MatrixO.content = {};

            /*
                 [.....]
                 [...b.]
                 [.....]
            [...]    |
            [...]    |
            [...]    |
            [.a.]----c
            [...]
            [...]
            */

            for(int i = 0 ; i < MatrixA.Height ; i++)
            {
                for(int j = 0 ; j < MatrixB.Width ; j++)
                {
                    TYPE cellAcumulate = 0;
                    for(int k = 0 ; k < MatrixA.Width ; k++)
                    {
                        cellAcumulate = cellAcumulate + MatrixA.content[i * MatrixA.Width + k] * MatrixB.content[k * MatrixB.Width + j];
                    }
                    MatrixO.content.push_back(cellAcumulate);
                }
            }

            return ;
        }
        else
        {
            cout << fowo.cOwOut.ConsoleQuick("error","dimensions of given matrices does not match");
            return;
        }
    }

    template <typename TYPE>
    void Scale (MOwOtrix_Container<TYPE> &MatrixA, TYPE f, MOwOtrix_Container<TYPE> &MatrixO)
    {
        if (!MatrixIsValid(MatrixA))
        {
            cout << fowo.cOwOut.ConsoleQuick("error","the given matrices cannot be computed");
            return;
        }

        MatrixO.Width = MatrixA.Width;
        MatrixO.Height = MatrixA.Height;
        MatrixO.ElementCount = MatrixO.Width * MatrixO.Height;
        MatrixO.content = {};

        for(int i = 0 ; i < MatrixO.ElementCount ; i++)
        {
            MatrixO.content.push_back(MatrixA.content[i] * f);
        }

        return;
    }

    template <typename TYPE>
    void Transpose (MOwOtrix_Container<TYPE> &MatrixA, MOwOtrix_Container<TYPE> &MatrixO)
    {
        if (!MatrixIsValid(MatrixA))
        {
            cout << fowo.cOwOut.ConsoleQuick("error","the given matrices cannot be computed");
            return;
        }

        MatrixO.Width = MatrixA.Height;
        MatrixO.Height = MatrixA.Width;
        MatrixO.ElementCount = MatrixO.Width * MatrixO.Height;
        MatrixO.content = {};

        for(int i = 0 ; i < MatrixA.Width ; i++)
        {
            for(int j = 0 ; j < MatrixA.Height ; j++)
            {
                MatrixO.content.push_back(MatrixA.content[j * MatrixA.Width + i]);
            }
        }

        return;
    }

};