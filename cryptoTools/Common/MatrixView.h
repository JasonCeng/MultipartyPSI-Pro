#pragma once
// This file and the associated implementation has been placed in the public domain, waiving all copyright. No restrictions are placed on its use. 
#include "Common/Defines.h"
#include <array>
#include "Common/ArrayView.h"


namespace osuCrypto
{


    template<class T>
    class MatrixView
    {

        T* mData;

        // Matrix is index by [rowIdx][columnIdx]
        std::array<u64, 2> mSize;
        bool mOwner;

    public:

        typedef T value_type;

        MatrixView()
            :mData(nullptr),
            mSize({ 0,0 }),
            mOwner(false)
        {
        }

        MatrixView(const MatrixView& av) :
            mData(av.mData),
            mSize(av.mSize),
            mOwner(false)
        { }

        MatrixView(MatrixView&& av) :
            mData(av.mData),
            mSize(av.mSize),
            mOwner(av.mOwner)
        {
            av.mData = nullptr;
            av.mSize = { 0,0 };
            av.mOwner = false;
        }


        MatrixView(u64 rowSize, u64 columnSize) :
            mData(new T[rowSize * columnSize]()),
            mSize({ rowSize, columnSize }),
            mOwner(true)
        { }


        MatrixView(T* data, u64 rowSize, u64 columnSize, bool owner) :
            mData(data),
            mSize({ rowSize, columnSize }),
            mOwner(owner)
        {}

        MatrixView(T* start, T* end, u64 numColumns) :
            mData(&*start),
            mSize({ (end - start) / numColumns, numColumns }),
            mOwner(false)
        {
        }

        template <class Iter>
        MatrixView(Iter start, Iter end, u64 numColumns, typename Iter::iterator_category *p = 0) :
            mData(&*start),
            mSize({ (end - start) / numColumns, numColumns }),
            mOwner(false)
        {
            //static_assert(std::is_same<Iter::value_type, T>::value, "Iter iter must have the same value_type as ArrayView");
            std::ignore = p;

        }

        //template<class C>
        //MatrixView(const C& cont, u64 numColumns, typename C::value_type* p = 0) :
        //    mData(&*((C&)cont).begin()),
        //    mSize({ (((C&)cont).end() - ((C&)cont).begin()) / numColumns, numColumns }),
        //    mOwner(false)
        //{
        //    static_assert(std::is_same<C::value_type, T>::value, "Container cont must have the same value_type as ArrayView");

        //    (void*)p;
        //}

        template<template<typename, typename...> class C, typename... Args>
        MatrixView(const C<T, Args...>& cont, u64 numColumns, typename C<T, Args...>::value_type* p = 0) :
            mData(&*((C<T, Args...>&)cont).begin()),
            mSize({ (((C<T, Args...>&)cont).end() - ((C<T, Args...>&)cont).begin()) / numColumns, numColumns }),
            mOwner(false)
        {
            //static_assert(std::is_same<C::value_type, T>::value, "Container cont must have the same value_type as ArrayView");
            std::ignore = p;

        }


        ~MatrixView()
        {
            if (mOwner) delete[] mData;
        }

        const MatrixView<T>& operator=(MatrixView<T>&& copy)
        {
            if (mOwner) delete[] mData;

            mData = copy.mData;
            mSize = copy.mSize;
            mOwner = copy.mOwner;

            copy.mData = nullptr;
            copy.mSize = std::array<u64, 2>{0, 0};
            copy.mOwner = false;

            return copy;
        }

        const MatrixView<T>& operator=(const MatrixView<T>& copy)
        {

            mData = copy.mData;
            mSize = copy.mSize;
            mOwner = false;

            return copy;
        }

        const std::array<u64, 2>& size() const { return mSize; }



        T* data() const { return mData; };
#ifndef NDEBUG
        ArrayIterator<T> begin() const 
        { 
            T* b = mData;
            T* c = mData;
            T* e = (T*)mData + (mSize[0] * mSize[1]);

            return ArrayIterator<T>(b, c, e);
        };
        ArrayIterator<T> end() const {
            T* e = (T*)mData + (mSize[0] * mSize[1]);
            return ArrayIterator<T>(mData, e, e); 
        }
#else
        T* begin() const { return mData; };
        T* end() const { return mData + mSize[0] * mSize[1]; }
#endif

        ArrayView<T> operator[](u64 rowIdx) const
        {
#ifndef NDEBUG
            if (rowIdx >= mSize[0]) throw std::runtime_error(LOCATION);
#endif

            return ArrayView<T>(mData + rowIdx * mSize[1], mSize[1]);
        }

    };
}

