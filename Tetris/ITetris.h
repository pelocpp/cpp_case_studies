#pragma once

class ITetris {

    // properties
    virtual int getNumRows();
    virtual int getNumCols();

    // game commands
    virtual void Start();
    virtual void Stop();
};
