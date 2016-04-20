#include "ComponentManager.h"

ComponentManager::ComponentManager()
{
    //ctor
}

ComponentManager::~ComponentManager(){
    for(auto& iter : components){
        delete iter.second;
    }
}

unsigned ComponentManager::getComponentTypeId(const std::type_index& typeIndex) const{

    auto mapItr = componentTypeIds.find(typeIndex);

    // Component already registered
    if (mapItr != componentTypeIds.end()){
        return mapItr->second;
    }

    // Component type not yet registered in the manager
    else{
        unsigned typeId = typeIndex.hash_code();

        std::pair<std::type_index, unsigned> pair(typeIndex, typeId);
        componentTypeIds.insert(pair);
        return typeId;
    }
}

uint64_t ComponentManager::getMaskKey(unsigned entityId, unsigned componentTypeId) const{
    uint64_t mask = 0;
    mask = (mask | entityId) << 32;
    mask |= componentTypeId;
    return mask;
}
