#include "Warlock.hpp"

Warlock::Warlock(const std::string &name, const std::string &title)
{
	this->name = name;
	this->title = title;
	std::cout << this->name << ": This looks like another boring day.\n";
}

Warlock::~Warlock(void)
{
	std::cout << this->name << ": My job here is done!\n";
}

const std::string	&Warlock::getName(void) const
{
	return (this->name);
}

const std::string	&Warlock::getTitle(void) const
{
	return (this->title);
}

void	Warlock::setTitle(const std::string &src)
{
	this->title = src;
}

void	Warlock::introduce(void) const
{
	std::cout << this->name << ": I am " << this->name << ", " << this->title << "!\n";
}

Warlock::Warlock(const Warlock &src)
{
	*this = src;
}

Warlock	&Warlock::operator=(const Warlock &src)
{
	this->name = src.name;
	this->title = src.title;
	return (*this);
}