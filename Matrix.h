#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

#include "Sequence.h"
#include "Pair.h"




template <typename T>
class Matrix{
private:
    DynamicArray<T>* items;
    int length;
    int width;
public:
    Matrix(T* _items, int _length, int _width):
            items (new DynamicArray<T>(_items, _length*_width)),
            length(_length),
            width (_width)
    {}

    int getLength(){
        return length;
    }

    int getWidth(){
        return width;
    }

    T Get(int i, int j){
        if(i<width && j<length)
            return items->Get(i*length+j);
        else throw Exception(1);
    }


    std::string String(){
        std::string res;
        for(int i = 0; i<width; i++) {
            for (int j = 0; j < length; j++)
                res += toString<T>(items->Get(i*length+j)) + ' ';
            res+='\n';
        }
        return res;
    }
};

class sparseMatrix{
private:
    DynamicArray<Pair<Pair<int, int>, int>> items = DynamicArray<Pair<Pair<int, int>, int>>();
    int length;
    int width;
public:
    sparseMatrix(Matrix<int> matrix):
            length(matrix.getLength()),
            width(matrix.getWidth())
    {
        for (int i = 0; i<matrix.getWidth(); i++)
            for(int j = 0; j<matrix.getLength(); j++)
                if(matrix.Get(i, j) != 0) items.Prepend(Pair<Pair<int,int>, int>(Pair<int,int>(i, j), matrix.Get(i, j)));
    }

    std::string String(){
        auto iter = items.begin();
        std::string res;
        for(int i = 0; i < width; i++) {
            for (int j = 0; j < length; j++)
                if (iter->isValuable()) {
                    if (iter->GetData().getLeft().getLeft() == i && iter->GetData().getLeft().getRight() == j) {
                        res += toString<int>(iter->GetData().getRight()) + ' ';
                        iter->Next();
                    } else res += "0 ";
                }
                else res += "0 ";
            res+='\n';
        }
        return res;
    }
};

#endif
