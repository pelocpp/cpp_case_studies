// =====================================================================================
// Examples.cpp
// =====================================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <forward_list>
#include <memory>

#include "Soldier.h"
#include "IJosephus.h"
#include "Josephus.h"
#include "Josephus.h"
#include "JosephusForwardListImpl.h"
#include "JosephusArrayImpl.h"

void test01_Josephus()
{
    JosephusForwardListImpl josephus{ };
    josephus.setPassBy(3);

    std::cout << "Number of soldiers: " << josephus.count() << std::endl;
    std::cout << "Eliminating: Each " << josephus.passBy() << ". soldier" << std::endl << std::endl;

    while (josephus.alive() > 1)
    {
        josephus.eliminateNextSoldier();
        std::cout << "Removed " << std::setw(2) << josephus.lastEliminated() << "  " << josephus << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Last eliminated soldier: " << josephus.lastEliminated() << std::endl;
    std::cout << "Last alive soldier:      " << josephus.lastAlive() << std::endl;
}

void test02_Josephus()
{
    JosephusForwardListImpl josephus{ };
    josephus.setPassBy(3);

    std::cout << "Number of soldiers: " << josephus.count() << std::endl;
    std::cout << "Eliminating: Each " << josephus.passBy() << ". soldier" << std::endl;
    josephus.eliminateAll();
    std::cout << "Last eliminated soldier: " << josephus.lastEliminated() << std::endl;
    std::cout << "Last alive soldier:      " << josephus.lastAlive() << std::endl;
}

void test03_Josephus()
{
    JosephusForwardListImpl josephus{ 41, 3 };
    josephus.setPassBy(3);

    std::cout << "Number of soldiers: " << josephus.count() << std::endl;
    std::cout << "Eliminating: Each " << josephus.passBy() << ". soldier" << std::endl << std::endl;

    while (josephus.alive() > 1)
    {
        josephus.eliminateNextSoldier();
        std::cout << "Removed " << std::setw(2) << josephus.lastEliminated() << "  " << josephus << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Last eliminated soldier: " << josephus.lastEliminated() << std::endl;
    std::cout << "Last alive soldier:      " << josephus.lastAlive() << std::endl;
}

void test04_Josephus()
{
    JosephusForwardListImpl josephus{ 41, 10 };
    josephus.setPassBy(3);

    std::cout << "Number of soldiers: " << josephus.count() << std::endl;
    std::cout << "Eliminating: Each " << josephus.passBy() << ". soldier" << std::endl;
    josephus.eliminateAll();
    std::cout << "Last eliminated soldier: " << josephus.lastEliminated() << std::endl;
    std::cout << "Last alive soldier:      " << josephus.lastAlive() << std::endl;
}

void test05_Josephus()
{
    JosephusArrayImpl josephus{ };
    josephus.setPassBy(3);

    std::cout << "Number of soldiers: " << josephus.count() << std::endl;
    std::cout << "Eliminating: Each " << josephus.passBy() << ". soldier" << std::endl << std::endl;

    while (josephus.alive() > 1)
    {
        josephus.eliminateNextSoldier();
        std::cout << "Removed " << std::setw(2) << josephus.lastEliminated() << "  " << josephus << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Last eliminated soldier: " << josephus.lastEliminated() << std::endl;
    std::cout << "Last alive soldier:      " << josephus.lastAlive() << std::endl;
}

void test06_Josephus()
{
    JosephusArrayImpl josephus{ };
    josephus.setPassBy(3);

    std::cout << "Number of soldiers: " << josephus.count() << std::endl;
    std::cout << "Eliminating: Each " << josephus.passBy() << ". soldier" << std::endl;
    josephus.eliminateAll();
    std::cout << "Last eliminated soldier: " << josephus.lastEliminated() << std::endl;
    std::cout << "Last alive soldier:      " << josephus.lastAlive() << std::endl;
}

void test07_Josephus()
{
    std::shared_ptr<IJosephus> sp = std::make_shared<JosephusForwardListImpl>(41, 3);
    sp->setPassBy(3);

    std::cout << "Number of soldiers: " << sp->count() << std::endl;
    std::cout << "Eliminating: Each " << sp->passBy() << ". soldier" << std::endl << std::endl;

    while (sp->alive() > 1)
    {
        sp->eliminateNextSoldier();
        std::cout << "Removed " << std::setw(2) << sp->lastEliminated() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Last eliminated soldier: " << sp->lastEliminated() << std::endl;
    std::cout << "Last alive soldier:      " << sp->lastAlive() << std::endl;
}

// =====================================================================================
// End-of-File
// =====================================================================================
