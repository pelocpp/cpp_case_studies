#pragma once

class IKeyboardListener {
public:
    virtual ~IKeyboardListener() {};

    // TODO: Klären, ob die beiden observer Zeiger const vereinbart werden können ?!?!?!

    virtual void attach(IKeyboardObserver* observer) = 0;
    virtual void detach(IKeyboardObserver* observer) = 0;
    virtual void notifyAll(std::deque<unsigned short>) = 0;
};
