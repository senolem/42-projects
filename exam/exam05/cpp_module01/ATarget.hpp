#pragma once

#include <iostream>

class ASpell;

class ATarget
{
    private:
        std::string type;
    
    public:
        ATarget(void);
        ATarget(std::string const &type);
        ATarget(ATarget const &src);
        ATarget &operator=(ATarget const &src);
        virtual ~ATarget();

        std::string const &getType(void) const;
        void getHitBySpell(ASpell const &src) const;
        virtual ATarget *clone(void) const = 0;
};

#include "ASpell.hpp"