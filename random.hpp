#include "stdafx/stdafx.h"

template<template<class>class Dist, class T>
static auto generate{
    [](T min, T max)noexcept
    {
        return [=]()noexcept{
            std::random_device rd{};
            std::mt19937 gen{ rd() };
            auto dist{ Dist<T>{ min, max } };
            return dist(gen);
        };
    }
};

template<template<class>class Dist = std::uniform_int_distribution, template<class>class C = std::vector, class T = uint8_t>
static auto gen_vec{
    []<class S>(S min, S max){
        return [=](S size){
            C<T> out(size);
            for(auto&& elm : out){
                elm = generate<Dist, T>(min, max)();
            }
            return out;
        };
    }
};
