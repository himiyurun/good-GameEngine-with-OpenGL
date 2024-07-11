#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_
#include <iostream>
#include <cstdlib>

#include <glad\glad.h>

#include "../src/Renderer/Object.h"

#define NONE    (0x00)
#define SQUARE  (0x01)
#define QUADS   (0x02)

template <typename V>
class Structure
{
    const V *rect;

    size_t vertexcount;

    float location[2];

    const char* imgname;

    const V *uv;

public:

    Structure(size_t vertexcount, const V* rect, float location[2], const char* imgname, const V *uv);

    //  virutal ~Structure();

    const V *(getRect() const) { return rect; }

    size_t getCount() const { return vertexcount; }

    const char *(getImgName() const) { return imgname; }

    const V *(getUv() const) { return uv; }
};

#endif  //  _STRUCTURE_H_

template <typename V>
inline Structure<V>::Structure(size_t vertexcount, const V *rect, float location[2], const char *imgname, const V *uv)
    : vertexcount(vertexcount)
    , rect(rect)
    , location{ location[0], location[1] }
    , imgname(imgname)
    , uv(uv)
{
}
