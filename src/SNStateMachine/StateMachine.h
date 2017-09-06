#ifndef SN_STATE_MACHINE_H
#define SN_STATE_MACHINE_H

#include <unordered_map>
#include <map>
#include <string>
#include <iostream>
#include <initializer_list>

namespace SurgeNight {

    template<typename StateType, typename OperatorType>
    class StateMachine
    {
    public:
        StateMachine(std::initializer_list<StateType> stateList) : m_lock(false)
        {
            for (auto &x : stateList)
                m_state[x];
            m_curIt = m_begIt = stateList.size() > 0 ? m_state.find(*stateList.begin()) : m_state.begin();
        }
        ~StateMachine() = default;

        void reset()
        {
            m_curIt = m_begIt;
        }

        const bool setState(const StateType &state)
        {
            auto it = m_state.find(state);
            if (it == m_state.end())
                return false;
            m_curIt = it;
            return true;
        }

        const bool addTransTable(const StateType &state, std::initializer_list<std::pair<OperatorType, StateType>> list)
        {
            if (m_lock)
                return false;
            auto it = m_state.find(state);
            if (it == m_state.end())
                return false;
            for (auto &x : list) {
                auto item = m_state.find(x.second);
                if (item == m_state.end()) {
                    it->second.clear();
                    return false;
                }
                it->second[x.first] = x.second;
            }
            return true;
        }

        const bool addTransTable(const StateType &begSt, const StateType &endSt, std::initializer_list<OperatorType> list)
        {
            if (m_lock)
                return false;
            auto it = m_state.find(begSt);
            if (it == m_state.end())
                return false;
            if (m_state.find(endSt) == m_state.end())
                return false;
            for (auto &x : list) {
                it->second[x] = endSt;
            }
        }

        void finish()
        {
            m_lock = true;
        }

        const bool isLock() const
        {
            return m_lock;
        }

        const bool operator()(const OperatorType &op)
        {
            auto it = m_curIt->second.find(op);
            if (it == m_curIt->second.end())
                return false;
            m_curIt = m_state.find(it->second);
            return true;
        }

        const bool is(const StateType &state)
        {
            return m_curIt->first == state;
        }

        friend std::ostream& operator<<(std::ostream &out, StateMachine &machine)
        {
            return out << static_cast<StateType>(machine);
        }

        operator StateType()
        {
            return m_curIt->first;
        }

    private:
        typedef typename std::unordered_map<OperatorType, StateType> TransMap;
        typedef typename std::map<StateType, TransMap> StateMap;
        StateMap m_state;
        typename StateMap::iterator m_curIt, m_begIt;
        bool m_lock;
    };

}

#endif // SN_STATE_MACHINE_H
