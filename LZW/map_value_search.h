#pragma once

template<typename TKey, typename TValue>
TKey find(std::map<TKey, TValue>& _map, TValue value) {
    for (auto it = _map.begin(); it != _map.end(); ++it)
        if (it->second == value)
            return it->first;
}
