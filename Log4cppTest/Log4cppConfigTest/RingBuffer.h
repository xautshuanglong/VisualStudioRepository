#pragma once

#include <iostream>

template <typename T>
class RingBuffer
{
public:
	RingBuffer();
	~RingBuffer();
};

template <typename T>
RingBuffer<T>::RingBuffer()
{
	std::cout << "RingBuffer::RingBuffer()" << std::endl;
}

template <typename T>
RingBuffer<T>::~RingBuffer()
{
	std::cout << "RingBuffer::~RingBuffer()" << std::endl;
}
