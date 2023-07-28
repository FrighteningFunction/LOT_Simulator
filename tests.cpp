/**
 * @file tests.cpp
 * @brief A játék bizonyos funcionalitásait gtesztelő fájl
 * @todo sajnos felületes, de a legfontosabb funkciókat teszteli.
 *
 * ha módosítások után ez nem fut le (gyökeres változtatások kivételével)
 * Azonnal át kell nézni a hiba okát!
*/

#include "control.h"
#include "Errors.h"
#include "LOT.h"

#include <memory>
#include <vector>
#include <sstream>

#include <gtest/gtest.h>

//Teszteljük a lotot

TEST(RESET, lotreset) {
    // Redirect std::cout
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    LOT& dorm = LOT::mutasdalotot();

    // Create some errors
    std::unique_ptr<FalseFireAlarm> error1 = std::make_unique<FalseFireAlarm>();
    std::unique_ptr<MixedUpEntryCards> error2 = std::make_unique<MixedUpEntryCards>();
    std::unique_ptr<MalfunctioningOven> error3 = std::make_unique<MalfunctioningOven>();

    (*dorm.getSzintek()[0]).push_back(std::move(error1));
    (*dorm.getSzintek()[1]).push_back(std::move(error2));
    (*dorm.getSzintek()[2]).push_back(std::move(error3));

    // Start removing
    dorm.Reset();
    dorm.print();

    // Store the output after resetting
    std::string after_reset = buffer.str();

    // The output after resetting should be a LOT with no errors
    // Construct the expected output
    std::string expected_output = "FOLDSZINT\n1. EMELET\n2. EMELET\n3. EMELET\n4. EMELET\n";
    EXPECT_EQ(after_reset, expected_output);

    // Restore std::cout
    std::cout.rdbuf(prevcoutbuf);
}


TEST(SPAWNERRORS, spawn){
    std::cout<<"\nLOT hibak spawnolasa\n";
    LOT& dorm=LOT::mutasdalotot();

    dorm.spawnerrors();
    dorm.ErrorShout();
    dorm.print();

    dorm.Reset();
}

TEST(SPAWNERRORS, ResolveError){
    std::cout<<"\nLOT hibak kitorlese\n";
    LOT& dorm=LOT::mutasdalotot();

    //létrehozunk néhány hibát
    std::unique_ptr<FalseFireAlarm> error1=std::make_unique<FalseFireAlarm>();
    std::unique_ptr<MixedUpEntryCards> error2=std::make_unique<MixedUpEntryCards>();
    std::unique_ptr<MalfunctioningOven> error3=std::make_unique<MalfunctioningOven>();

    (*dorm.getSzintek()[0]).push_back(std::move(error1));
    (*dorm.getSzintek()[1]).push_back(std::move(error2));
    (*dorm.getSzintek()[2]).push_back(std::move(error3));

    std::cout<<"eltavolitas elott:\n";
    dorm.print();

    dorm.ResolveError(0);
    dorm.ResolveError(10);
    dorm.ResolveError(20);

    std::cout<<"eltavolitas utan:\n";
    dorm.print();

    dorm.Reset();
}

class IO : public ::testing::Test {
protected:
    LOT& dorm=LOT::mutasdalotot();

    // The stringstream to use as the source of "user input"
    std::stringstream fakeInput;

    // Save the original values of cin and cout
    std::streambuf* originalCin = std::cin.rdbuf();

    void SetUp() override {

        // Redirect cin
        std::cin.rdbuf(fakeInput.rdbuf());
    }

    void TearDown() override {
        dorm.Reset();

        // Reset cin and cout to their original values
        std::cin.rdbuf(originalCin);

        // Reset the global variables to their original values
        Corp = 100;
        Stud = 100;
        Score = 0;
        HP = 3;
        days = 0;
    }
};

TEST_F(IO, Beker) {
    // Test handling of non-numeric input, then out of range floor, then out of range error index,
    // and finally a valid input
    (*dorm.getSzintek().at(1)).push_back(std::make_unique<FalseFireAlarm>());

    fakeInput.str("test\n60\n11\n10\n");
    EXPECT_EQ(valaszbeker(dorm), 10);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}