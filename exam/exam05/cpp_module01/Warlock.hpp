#pragma once

#include <iostream>
#include "ASpell.hpp"
#include "ATarget.hpp"
#include <map>

class Warlock
{
    private:
        std::string name;
        std::string title;

        Warlock(void);
        Warlock(Warlock const &other);
        Warlock &operator=(Warlock const &other);

        std::map<std::string, ASpell *> arr;
    public:
        Warlock(std::string const &name, std::string const &title);
        ~Warlock();

        std::string const &getName(void) const;
        std::string const &getTitle(void) const;

        void setTitle(std::string const &title);
        void introduce(void) const;
        void learnSpell(ASpell *src);
        void forgetSpell(std::string name);
        void launchSpell(std::string name, ATarget const &src);
};