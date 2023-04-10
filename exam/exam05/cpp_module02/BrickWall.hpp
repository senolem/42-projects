#pragma once

#include "ATarget.hpp"

class BrickWall: public ATarget
{
    public:
        BrickWall(void);
        ~BrickWall(void);

        virtual ATarget *clone(void) const;
};