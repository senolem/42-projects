#include "ASpell.hpp"

ASpell::ASpell(void)
{

}

ASpell::ASpell(std::string const &name, std::string const &effects)
{
    this->name = name;
    this->effects = effects;
}

ASpell::ASpell(ASpell const &src)
{
	*this = src;
}

ASpell &ASpell::operator=(ASpell const &src)
{
    this->name = src.name;
    this->effects = src.effects;
    return (*this);
}

ASpell::~ASpell(void)
{

}

std::string const &ASpell::getName(void) const
{
	return (this->name);
}

std::string const &ASpell::getEffects(void) const
{
	return (this->effects);
}

void ASpell::launch(ATarget const &src) const
{
    src.getHitBySpell(*this);
}