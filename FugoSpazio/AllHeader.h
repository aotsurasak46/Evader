#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <utility>
#include <algorithm>
#include <string.h>
#include <sstream>

using namespace sf;     // sfml
using namespace std;    // standard

inline Vector2f normalize(Vector2f vec)
{
    float len = sqrtf(vec.x * vec.x + vec.y * vec.y);
    if (len != 0)
        return vec / len;
    return vec;
}

inline int randint(int start, int stop)
{

    return (rand() % (stop - start)) + start;

}