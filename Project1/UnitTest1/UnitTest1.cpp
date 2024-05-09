#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestDeleteHalfTeams)
        {
            Team* first = nullptr;
            Team* last = nullptr;
            insertTeam(first, last, "Team1", 10);
            insertTeam(first, last, "Team2", 20);
            insertTeam(first, last, "Team3", 15);
            insertTeam(first, last, "Team4", 5);
            insertTeam(first, last, "Team5", 25);

            int expectedRemainingTeams = 3;

            deleteHalfTeams(first, last);

            int actualRemainingTeams = 0;
            Team* current = first;
            while (current != nullptr) {
                actualRemainingTeams++;
                current = current->next;
            }
            Assert::AreEqual(expectedRemainingTeams, actualRemainingTeams);

            string expectedTeamNames[3] = { "Team2", "Team3", "Team5" };

            current = first;
            for (int i = 0; i < expectedRemainingTeams; i++) {
                Assert::AreEqual(expectedTeamNames[i], current->name);
                current = current->next;
            }
        }
    };
}