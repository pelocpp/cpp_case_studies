#pragma once

class IKeyboardObserver {
public:
    // TODO: Wird der auch aufgerufen ?!?!?
    virtual ~IKeyboardObserver() {};
    virtual void update(std::deque<unsigned short>) = 0;
};