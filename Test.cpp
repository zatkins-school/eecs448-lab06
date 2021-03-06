/**
*	@file Test.cpp
*	@author Zachary Atkins
*	@date 11/2/2018
*	@brief Implementation file for Test class
*/
#include "Test.hpp"

Test::Test()
{
    list = new LinkedListOfInts();
}

Test::~Test()
{
    delete list;
}

void Test::reportBug(string context, string bug){
    string bugString = context + " " + bug;
    for (string b: failedTests) {
        if (b == bugString) return;
    }
    failedTests.push_back(bugString);
}

string Test::testIsEmpty()
{
    stringstream output;
    vector<int> testAgainst = list->toVector();
    // Check if vector is empty
    string expected = testAgainst.size() == 0 ? "True" : "False";
    output << "\tExpected: " << expected << endl;
    // Check is isEmpty returns true
    string actual = list->isEmpty() ? "True" : "False";
    output << "\tActual: " << actual << endl;
    /**
     * ? If: vector and list agree on whether list is empty
     * ? True: Test was passed
     * ? False: Test failed, add bug string to failedTest
     */
    if (expected == actual) {
        output << "\tResult: Passed!" << endl;
    } else {
        output << "\tResult: Failed." << endl;
        if (testAgainst.size() > 0) {
            reportBug("LinkedListOfInts::isEmpty","returns true when list is not empty.");
        } else {
            reportBug("LinkedListOfInts::isEmpty","returns false when list is empty.");
        }
    }
    return output.str();
}


string Test::testSize()
{
    stringstream output;
    vector<int> testAgainst = list->toVector();
    output << "\tExpected: " << testAgainst.size() << endl;
    output << "\tActual: " << list->size() << endl;
    /**
     * ? If: vector and list agree on list size
     * ? True: Test was passed
     * ? False: Test failed, add bug string to failedTest
     */
    if (testAgainst.size() == list->size()) {
        output << "\tResult: Passed!" << endl;
    } else {
        output << "\tResult: Failed." << endl;
        reportBug("LinkedListOfInts::size","returns incorrect value.");
    }
    return output.str();
}

string Test::testSearch(int value)
{
    stringstream output;
    vector<int> testAgainst = list->toVector();
    bool found = false;
    for (int val: testAgainst) {
        if (val == value) {
            found = true;
        }
    }
    string expected = found ? "True" : "False";
    output << "\tExpected: " << expected << endl;
    string actual = list->search(value) ? "True" : "False";
    output << "\tActual: " << actual << endl;
    if (expected == actual) {
        output << "\tResult: Passed!" << endl;
    } else {
        output << "\tResult: Failed." << endl;
        if (actual == "True") {
            reportBug("LinkedListOfInts::search","returns false for element in list.");
        } else {
            reportBug("LinkedListOfInts::search","returns true for element not in list.");
        }
    }
    return output.str();
}

string Test::testAddBack(int value)
{
    stringstream output;
    vector<int> testAgainst = list->toVector();
    testAgainst.push_back(value);
    output << "\tExpected: " << displayVector(testAgainst) << endl;
    list->addBack(value);
    output << "\tActual: " << displayList() << endl;
    /**
     * ? If: vector and list
     * ? True: Test was passed
     * ? False: Test failed, add bug string to failedTest
     */
    if (testAgainst == list -> toVector()) {
        output << "\tResult: Passed!" << endl;
    } else {
        output <<  "\tResult: Failed." << endl;
        reportBug("LinkedListOfInts::addBack","does not add to the back.");
    }
    int size = testAgainst.size();
    testAgainst = list -> toVector();
    /**
     * ? If: vector and list agree on whether list is empty
     * ? True: Test was passed
     * ? False: Test failed, add bug string to failedTest
     */
    if (size != testAgainst.size()) {
        reportBug("LinkedListOfInts::addBack","fails to add.");
    }
    return output.str();
}

string Test::testAddFront(int value)
{
    stringstream output;
    vector<int> testAgainst = list->toVector();
    testAgainst.insert(testAgainst.begin(), value);
    output << "\tExpected: " << displayVector(testAgainst) << endl;
    list->addFront(value);
    output << "\tActual: " << displayList() << endl;
    if (testAgainst == list -> toVector()) {
        output << "\tResult: Passed!" << endl;
    } else {
        output <<  "\tResult: Failed." << endl;
        reportBug("LinkedListOfInts::addFront","does not add to the front.");
    }
    int size = testAgainst.size();
    testAgainst = list -> toVector();
    if (size != testAgainst.size()) {
        reportBug("LinkedListOfInts::addFront","fails to add.");
    }
    return output.str();
}

string Test::testRemoveBack()
{
    stringstream output;
    vector<int> testAgainst = list->toVector();
    int preSize = testAgainst.size();
    bool expected = testAgainst.size() != 0;
    if (expected)
    {
        testAgainst.pop_back();
        output << "\tExpected: " << displayVector(testAgainst) << endl;
        bool actual = list->removeBack();
        output << "\tActual: " << displayList() << endl;
        if (expected == actual) {
            output << "\tResult: Passed!\n";
        } else {
            output << "\tResult: Failed.\n";
            reportBug("LinkedListOfInts::removeBack","returns false when list is not empty.");
        }
        output << "Testing if LinkedListOfInts::removeBack removed an element...\n\tResult: ";
        testAgainst = list->toVector();
        if (testAgainst.size() == preSize - 1) {
            output << "Passed!\n";
        } else {
            output << "Failed\n";
            reportBug("LinkedListOfInts::removeBack","fails to remove.");
        }
    }
    else {
        output << "\tExpected: " << "False" << endl;
        bool actual = list->removeBack();
        string actualStr = actual ? "True" : "False";
        output << "\tActual: " << actualStr << endl;
        if (expected == actual) {
            output << "\tResult: Passed!" << endl;
        } else {
            output << "\tResult: Failed." << endl;
            reportBug("LinkedListOfInts::removeBack","returns true when list is empty.");
        }
    }
    return output.str();
}

string Test::testRemoveFront()
{
    stringstream output;
    vector<int> testAgainst = list->toVector();
    int preSize = testAgainst.size();
    bool expected = testAgainst.size() != 0;
    if (expected)
    {
        testAgainst.erase(testAgainst.begin());
        output << "\tExpected: " << displayVector(testAgainst) << endl;
        bool actual = list->removeFront();
        output << "\tActual: " << displayList() << endl;
        string test;
        if (expected == actual) {
            output << "\tResult: Passed!\n";
        } else {
            output << "\tResult: Failed.\n";
            reportBug("LinkedListOfInts::removeFront","returns false when list is not empty.");
        }
        output << "Testing if LinkedListOfInts::removeFront removed an element...\n\tResult: ";
        testAgainst = list->toVector();
        if (testAgainst.size() == preSize - 1) {
            output << "Passed!\n";
        } else {
            output << "Failed\n";
            reportBug("LinkedListOfInts::removeFront","fails to remove.");
        }
    }
    else {
        output << "\tExpected: " << "False" << endl;
        bool actual = list->removeFront();
        string actualStr = actual ? "True" : "False";
        output << "\tActual: " << actualStr << endl;
        if (expected == actual) {
            output << "\tResult: Passed!" << endl;
        } else {
            output << "\tResult: Failed." << endl;
            reportBug("LinkedListOfInts::removeFront","returns true when list is empty.");
        }
    }
    return output.str();
}

void Test::runTests()
{
    cout << "Starting Test Suite...\n======================\n";
    cout << "Testing LinkedListOfInts::isEmpty when empty\n-------------------------------------------\n";
    cout << testIsEmpty() << endl;
    cout << "Testing LinkedListOfInts::size when empty\n-----------------------------------------\n";
    cout << testSize() << endl;

    cout << "Testing LinkedListOfInts::removeBack when empty\n------------------------------------------\n";
    cout << testRemoveBack() << endl;

    cout << "Testing LinkedListOfInts::removeFront when empty\n-------------------------------------------\n";
    cout << testRemoveFront() << endl;

    cout << "Testing LinkedListOfInts::addFront twice\n----------------------------------------\n";
    cout << testAddFront(1);
    cout << testAddFront(2) << endl;

    cout << "Testing LinkedListOfInts::size when nonempty\n--------------------------------------------\n";
    cout << testSize() << endl;
    cout << "Testing LinkedListOfInts::isEmpty when not empty\n------------------------------------------------\n";

    cout << testIsEmpty() << endl;

    cout << "Testing LinkedListOfInts::search\n--------------------------------\n";
    cout << "For value=2 (in list):"<<endl;
    cout << testSearch(2);
    cout << "For value=4 (not in list):" << endl;
    cout << testSearch(4) << endl;

    cout << "Testing LinkedListOfInts::addBack\n---------------------------------\n";
    cout << testAddBack(3) << endl;

    cout << "Testing LinkedListOfInts::removeBack when nonempty\n--------------------------------------------------\n";
    cout << testRemoveBack() << endl;

    cout << "Testing LinkedListOfInts::removeFront when nonempty\n---------------------------------------------------\n";
    cout << testRemoveFront();

    // open a file stream and write bug results
    ofstream testResults;
    testResults.open("BugTestResults.txt");
    if (failedTests.size()>0) {
        cout << "~~~~~~~~~~~~~~~~\n" << "| FAILED TESTS |\n" << "~~~~~~~~~~~~~~~~\n";
        testResults << "~~~~~~~~~~~~~~~~\n" << "| FAILED TESTS |\n" << "~~~~~~~~~~~~~~~~\n";
        int size = failedTests.size();
        for (int i = 0; i < size; i++) {
            cout << i+1 << ". " << failedTests[i] << endl;
            testResults << i+1 << ". " << failedTests[i] << endl;
        }
    }
    else {
        testResults << "~~~~~~~~~~~~~~~~~~~~\n" << "| ALL TESTS PASSED |\n" << "~~~~~~~~~~~~~~~~~~~~\n";
    }
    testResults.close();
}

string Test::displayList() {
    vector<int> v = list->toVector();
    return displayVector(v);
}

string Test::displayVector(vector<int> vect) {
    string s = "[";
    int size = vect.size();
    for (int i = 0; i < size; i++) {
        s+= to_string(vect[i]);
        if (i < size - 1){
            s += ",";
        }
    }
    return s + "]";
}
