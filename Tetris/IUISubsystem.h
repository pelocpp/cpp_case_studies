#pragma once

class IUISubsystem {

public:
    // properties
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;

    // public interface
    virtual void initConsole() = 0;
    virtual void showConsole() = 0;
    virtual void closeConsole() = 0;

    // getter
    virtual bool isInputAvailable() = 0;
    virtual bool isEscapeHit() = 0;
};
