#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator(void)
{

}

TargetGenerator::~TargetGenerator(void)
{
    std::map<std::string, ATarget *>::iterator iter = this->arr_target.begin();
    std::map<std::string, ATarget *>::iterator iter2 = this->arr_target.end();
    while (iter != iter2)
    {
        delete iter->second;
        ++iter;
    }
    this->arr_target.clear();
}

void TargetGenerator::learnTargetType(ATarget* target_ptr)
{
    if (target_ptr)
        arr_target.insert(std::pair<std::string, ATarget *>(target_ptr->getType(), target_ptr->clone()));
}

void TargetGenerator::forgetTargetType(const std::string &target_name)
{
    std::map<std::string, ATarget *>::iterator iter = arr_target.find(target_name);

	if (iter != arr_target.end())
		delete iter->second;
    arr_target.erase(target_name);
}

ATarget* TargetGenerator::createTarget(const std::string &target_name)
{
    std::map<std::string, ATarget *>::iterator iter = arr_target.find(target_name);

    if (iter != arr_target.end())
        return arr_target[target_name];
    return NULL;
}
