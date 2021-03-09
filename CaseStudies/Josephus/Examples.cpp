// =====================================================================================
// ExamplesJosephus.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <array>
#include <forward_list>

#include "Soldier.h"
#include "Josephus.h"
#include "JosephusEx.h"

void test01_Josephus()
{
    Josephus j{};
    j.setPassBy(3);

    std::cout << "Number of soldiers: " << j.count() << std::endl;
    std::cout << "Eliminating: Each " << j.passBy() << ". soldier" << std::endl;
    std::cout << j << std::endl;
}

void test02_Josephus()
{
    Josephus j{ 41 };
    j.setPassBy(5);

    std::cout << "Number of soldiers: " << j.count() << std::endl;
    std::cout << "Eliminating: Each " << j.passBy() << ". soldier" << std::endl;
    std::cout << j << std::endl;
}

void test03_Josephus()
{
    Josephus j{ 17 };
    j.setPassBy(3);

    std::cout << "Number of soldiers: " << j.count() << std::endl;
    std::cout << "Eliminating: Each " << j.passBy() << ". soldier" << std::endl << std::endl;

    while (j.alive() > 1)
    {
        j.eliminateNextSoldier();
        std::cout << "Removed ";
        std::cout.width(2);
        std::cout << j.lastEliminated() << "   " << j << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Last eliminated soldier: " << j.lastEliminated() << std::endl;
    std::cout << "Last alive soldier:      " << j.lastAlive() << std::endl;
}

void test04_Josephus()
{
    Josephus j{ 41 };
    j.setPassBy(3);

    std::cout << "Number of soldiers: " << j.count() << std::endl;
    std::cout << "Eliminating: Each " << j.passBy() << ". soldier" << std::endl << std::endl;

    while (j.alive() > 1)
    {
        j.eliminateNextSoldier();
        std::cout << "Removed ";
        std::cout.width(2);
        std::cout << j.lastEliminated() << "   " << j << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Last eliminated soldier: " << j.lastEliminated() << std::endl;
    std::cout << "Last alive soldier:      " << j.lastAlive() << std::endl;
}

// =====================================================================================
// End-of-File
// =====================================================================================


void test05_Josephus()
{
    JosephusEx j{ };
    j.setPassBy(3);

    std::cout << "Number of soldiers: " << j.count() << std::endl;
    std::cout << "Eliminating: Each " << j.passBy() << ". soldier" << std::endl << std::endl;

    while (j.alive() > 1)
    {
        j.eliminateNextSoldier();
        std::cout << "Removed ";
        std::cout.width(2);
        std::cout << j.lastEliminated() << "   " << j << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Last eliminated soldier: " << j.lastEliminated() << std::endl;
    std::cout << "Last alive soldier:      " << j.lastAlive() << std::endl;
}
