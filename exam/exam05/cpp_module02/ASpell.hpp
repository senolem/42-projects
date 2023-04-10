#pragma once

#include <iostream>

class ATarget;

class ASpell
{
    private:
        std::string name;
        std::string effects;

    public:
        ASpell(void);
        ASpell(std::string const &name, std::string const &effects);
        ASpell(ASpell const &src);
        ASpell &operator=(ASpell const &src);
        virtual ~ASpell(void);

        std::string const &getName(void) const;
        std::string const &getEffects(void) const;
        void launch(ATarget const &src) const;
        virtual ASpell *clone() const = 0;
};

#include "ATarget.hpp"