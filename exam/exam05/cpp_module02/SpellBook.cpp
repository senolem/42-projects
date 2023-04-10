#include "SpellBook.hpp"

SpellBook::SpellBook(void)
{

}

SpellBook::~SpellBook(void)
{
    std::map<std::string, ASpell *>::iterator iter = this->arr_spell.begin();
    std::map<std::string, ASpell *>::iterator iter2 = this->arr_spell.end();
    while (iter != iter2)
    {
        delete iter->second;
        ++iter;
    }
    this->arr_spell.clear();
}

void SpellBook::learnSpell(ASpell* spell_ptr)
{
    if (spell_ptr)
        arr_spell.insert(std::pair<std::string, ASpell *>(spell_ptr->getName(), spell_ptr->clone()));
}

void SpellBook::forgetSpell(std::string const &spell_name)
{
    std::map<std::string, ASpell *>::iterator iter = arr_spell.find(spell_name);
	if (iter != arr_spell.end())
		delete iter->second;
    arr_spell.erase(spell_name);
}

ASpell* SpellBook::createSpell(std::string const &spell_name)
{
    std::map<std::string, ASpell *>::iterator iter = arr_spell.find(spell_name);
    if (iter != arr_spell.end())
        return arr_spell[spell_name];
    return NULL;
}
