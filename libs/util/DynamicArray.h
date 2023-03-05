#ifndef _DYNAMIC_ARRAY
#define _DYNAMIC_ARRAY

#include "mbed.h"

template <typename T>
struct DynamicArray
{
private:
    T *mData;
    unsigned mSize = 0;
    unsigned mCapacity;
    bool mStatus;

public:
    DynamicArray<T>(unsigned initialCapacity = 1) : mStatus(true), mSize(0), mCapacity(initialCapacity)
    {
        mData = (T *)malloc(initialCapacity * sizeof(T));
        if (mData == 0)
        {
            // Failed to initialize
            mStatus = false;
        }
    }

    T operator[](int index)
    {
        return mData[index];
    }

    unsigned size()
    {
        return mSize;
    }

    void push(T item)
    {
        if (mSize >= mCapacity)
        {
            resize();
        }

        memcpy((void *)&item, mData + mSize * sizeof(T), sizeof(T));
        mSize++;
    }

    void remove(unsigned index)
    {
        if (index < 0 || index > mCapacity - 1)
        {
            return;
        }

        leftShift(index);
        mSize--;

        if (shouldShirink())
        {
            shrink();
        }
    }

    T pop()
    {
        mSize--;
        return mData[mSize + 1];
    }

private:
    void resize()
    {
        // Attempt to double the space
        T *newData = (T *)malloc((mCapacity * 2) * sizeof(T));
        if (newData == 0)
        {
            mStatus = false;
            return;
        }

        // Copy over previous stored elements
        unsigned newCapacity = mCapacity * 2;
        for (unsigned i = 0; i < mCapacity; ++i)
        {
            newData[i] = mData[i];
        }

        // Update
        mCapacity = newCapacity;
        free(mData);
        mData = newData;
    }

    bool shouldShirink()
    {
        return mSize + 1 < (mCapacity / 2);
    }

    void shrink()
    {
        unsigned newCapacity = (mCapacity / 2) + 1;
        T *newData = (T *)malloc(newCapacity * sizeof(T));

        // Copy over previous stored elements
        for (unsigned i = 0; i < newCapacity; ++i)
        {
            newData[i] = mData[i];
        }

        // Update
        mCapacity = newCapacity;
        free(mData);
        mData = newData;
    }

    void leftShift(unsigned startIdx)
    {
        // Starting at the index, left shift everything
        for (unsigned i = startIdx; i < mCapacity - 1; ++i)
        {
            mData[i] = mData[i + 1];
        }
    }

public:
    ~DynamicArray()
    {
        free(mData);
    }
};

#endif