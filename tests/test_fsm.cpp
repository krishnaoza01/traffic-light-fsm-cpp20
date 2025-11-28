#include <iostream>
#include "../src/StateMachine.hpp"

enum class TestState { A, B, C };

int main() {
    StateMachine<TestState> fsm;

    fsm.addState(TestState::A, [](){ std::cout << "Enter A\n"; },
                              [](){ std::cout << "Exit A\n"; });

    fsm.addState(TestState::B, [](){ std::cout << "Enter B\n"; },
                              [](){ std::cout << "Exit B\n"; });

    fsm.addState(TestState::C, [](){ std::cout << "Enter C\n"; },
                              [](){ std::cout << "Exit C\n"; });

    fsm.addTransition(TestState::A, TestState::B);
    fsm.addTransition(TestState::B, TestState::C);

    fsm.setInitial(TestState::A);

    std::cout << "Testing Transition A → B\n";
    fsm.transition(TestState::B);

    std::cout << "Testing Transition B → C\n";
    fsm.transition(TestState::C);

    std::cout << "All tests finished.\n";

    return 0;
}
