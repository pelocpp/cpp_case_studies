#pragma once

class IKeyboardListener {
public:
    virtual ~IKeyboardListener() {};

    // TODO: Kl�ren, ob die beiden observer Zeiger const vereinbart werden k�nnen ?!?!?!

    virtual void attach(IKeyboardObserver* observer) = 0;
    virtual void detach(IKeyboardObserver* observer) = 0;
    virtual void notifyAll(std::deque<unsigned short>) = 0;
};
