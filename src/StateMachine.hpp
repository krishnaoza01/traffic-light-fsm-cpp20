#pragma once
#include <string>
#include <functional>
#include <unordered_map>

// Generic finite state machine template
template <typename StateType>
class StateMachine {
public:
    using Callback = std::function<void()>;

    struct StateInfo {
        Callback onEnter;
        Callback onExit;
    };

    void addState(StateType state, Callback onEnter, Callback onExit) {
        states[state] = {onEnter, onExit};
    }

    void addTransition(StateType from, StateType to) {
        transitions[from].push_back(to);
    }

    bool canTransition(StateType from, StateType to) {
        auto &vec = transitions[from];
        return std::find(vec.begin(), vec.end(), to) != vec.end();
    }

    bool transition(StateType next) {
        if (!canTransition(current, next))
            return false;

        if (states[current].onExit) states[current].onExit();
        current = next;
        if (states[current].onEnter) states[current].onEnter();
        return true;
    }

    StateType getState() const { return current; }
    void setInitial(StateType initial) { current = initial; }

private:
    std::unordered_map<StateType, StateInfo> states;
    std::unordered_map<StateType, std::vector<StateType>> transitions;
    StateType current;
};
