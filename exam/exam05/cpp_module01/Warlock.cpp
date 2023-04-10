#include "Warlock.hpp"

Warlock::Warlock(std::string const &name, std::string const &title) : name(name), title(title)
{
    std::cout << this->name << ": This looks like another boring day.\n";
}

Warlock::~Warlock(void)
{
    std::map<std::string, ASpell *>::iterator iter = this->arr.begin();
    std::map<std::string, ASpell *>::iterator iter2 = this->arr.end();

	std::cout << this->name << ": My job here is done!\n";
    while (iter != iter2)
    {
        delete iter->second;
        ++iter;
    }
    this->arr.clear();
}

std::string const &Warlock::getName(void) const
{
	return (this->name);
}

std::string const &Warlock::getTitle(void) const
{
	return (this->title);
}

void Warlock::setTitle(std::string const &title)
{
	this->title = title;
}

void Warlock::introduce(void) const
{
	std::cout << this->name << ": I am " << this->name << ", " << this->title << "!\n";
}

void Warlock::learnSpell(ASpell *src)
{
	if (src)
		arr.insert(std::pair<std::string, ASpell *>(src->getName(), src->clone()));
}

void Warlock::forgetSpell(std::string name)
{
	std::map<std::string, ASpell *>::iterator iter = arr.find(name);

	if (iter != arr.end())
		delete iter->second;
	arr.erase(name);
}

void Warlock::launchSpell(std::string name, ATarget const &src)
{
	ASpell* spell = arr[name];

	if (spell)
		spell->launch(src);
}
