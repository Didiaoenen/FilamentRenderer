#include "FRMaterialInstanceWarp.h"

template<typename T>
void FR::FRMaterialInstanceWarp::SetParameter(const std::string& pName, T const& value)
{
    if (auto material = PtrValue(this)->getMaterial(); material->hasParameter(pName.c_str()))
    {
        PtrValue(this)->setParameter(pName.c_str(), value);
    }
}