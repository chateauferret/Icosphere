//
// Created by martin on 20/09/18.
//

#ifndef ICOSPHERE_TRIANGLESELECTOR_H
#define ICOSPHERE_TRIANGLESELECTOR_H

#include "triangle.h"

namespace Halifirien {
    class TriangleSelector {
    public:
        TriangleSelector();
        ~TriangleSelector();
        virtual bool isSelected (const Triangle& t) const;
    };
}

#endif //ICOSPHERE_TRIANGLESELECTOR_H
