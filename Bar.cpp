/***********************************************************
** File:    Bar.cpp
** Project: CMSC 202 - Project 5
** Author:  Vy Nguyen
** Section: 12 - David Opie 
** Date:     4/20/2023
** Description: This program writes the functions associated with Bar.h
**********************************************************/

#include "Bar.h"

// Name: Bar (Default Constructor) (not used)
// Desc: Dynamically allocates m_data for strings (always). m_fileName defaults to test.txt
// Preconditions: Input file has correctly formatted input
// Postconditions: Returns list of items and their frequency (stored in LL)
Bar::Bar()
{
    m_data = new LL<string>();
    m_fileName = "test.txt"; 
}

// Name: Bar (Overloaded Constructor)
// Desc: Used to pass an input file
//       Dynamically allocates m_data for strings (always)
//       Sets m_fileName and nothing done with m_dataSorted until SortData
// Preconditions: Input file
// Postconditions: m_data is allocated, m_fileName populated
Bar::Bar(string filename)
{
    m_data = new LL<string>();
    m_fileName = filename;
}

// Name: ~Bar (Destructor)
// Desc: Deallocates m_data
// Preconditions: m_data has been dynamically allocated
// Postconditions: m_data is empty
Bar::~Bar()
{
    delete m_data; 
}

// Name: Start
// Desc: Calls LoadFile, RemoveCommon, RemoveSingles, Sort, DisplayBars, and Export
//       During testing, may want to call Display
// Preconditions: None (filename is available)
// Postconditions: None
void Bar::Start()
{
    LoadFile();
    RemoveCommon();
    RemoveSingles();
    SortData();
    DisplayBars();
    Export();
}

// Name: LoadFile()
// Desc: Loads a file (everything as a string although could be anything string-like)
//       Calls RemovePunct as each item is loaded
//       Each input file is an unknown length
// Preconditions: m_fileName is populated with good data
// Postconditions: m_data is populated
void Bar::LoadFile()
{
    string myString; // initialize string 
    ifstream infile(m_fileName); // open file 
    int dataCount = 0; 
    while (infile >> myString) // traverse the file 
    {
        RemovePunct(myString); // remove punct for each item
        m_data->Insert(myString); // insert into vector 
        ++dataCount; 
    }
    cout << dataCount << " loaded." << endl; 
    infile.close(); // close file
}


// Name: RemovePunct (passed a string)
// Desc: Converts all input into lowercase using tolower
//       When passed a string, removes all non letter punctation on the beginning
//       or end of the string.
//       These are all ok: "don't" "inner-circle" but "candy," is bad
//       Is called during LoadFile
//       You can use ispunct - https://www.geeksforgeeks.org/ispunct-function-c/
// Preconditions: Strings to be evaluated
// Postconditions: Punctuation is removed from string
void Bar::RemovePunct(string& myString)
{  
    int endOfString = myString.length() - 1; 
    int startOfString = 0; 
    
    // check for punct at the beginning, then erase it 
    if (ispunct(myString[startOfString]))
    {
        myString.erase(startOfString , startOfString + 1);
    }

    // if there is if there is punctation on the end, erase that too 
    if (ispunct(myString[endOfString]))
    {
        myString.erase(endOfString, endOfString + 1);
    }

    // double check for newlines at the end
    if ((myString[endOfString]) == '\n')
    {
        myString.erase(endOfString, endOfString + 1);
        // then take care of any remaining puncts as well 
        if (ispunct(myString[endOfString - 1]))
        {
            myString.erase(endOfString - 1, endOfString);
        }
    }

    // traverse the string using iterators 
    for (string::iterator it = myString.begin(); it != myString.end(); ++it)
    {
        // and turn every char into lowercase 
        *it = tolower(*it); 
    }
    // note to self: there is no need to delete/deallocate 
    // the string because RemovePunct() runs 
    // before inserting/allocating memory anyways 
}


// Name: RemoveCommon
// Desc: Asks user if they want to remove common words
//       If yes, iterates through m_data and removes all common words after they are read
// Preconditions: m_data is populated and EXCLUDE_LIST is populated
// Postconditions: m_data will have no words from EXCLUDE_LIST
void Bar::RemoveCommon()
{
    // initalize userChoice and ask user if they want to remove common words 
    string userChoice;
    cout << "Would you like to remove all common words (Only use with essays)?" << endl; 
    cin >> userChoice;
    // local constants for the user options 
    const string UPPERCASE_YES = "YES"; 
    const string LOWERCASE_YES = "yes"; 
    const string UPPERCASE_Y = "Y";
    const string LOWERCASE_Y = "y";

    // if the user indicates that they want to remove common words
    if ((userChoice == UPPERCASE_YES) or (userChoice == LOWERCASE_YES) or (userChoice == UPPERCASE_Y) or (userChoice == LOWERCASE_Y))
    {
        // first check if the list is empty 
        if (m_data->GetSize() == 0)
        {
            cout << "m_data is empty." << endl; 
        }
        // otherwise: 
        else
        {
            // use a const iterator to traverse the EXCLUDE_LIST 
            for (vector<string>::const_iterator it = EXCLUDE_LIST.begin(); it != EXCLUDE_LIST.end(); ++it)
            {
                // nested within this loop, traverse the LL using the overloaded [ ] operator and m_size
                for (int j = 0; j < m_data->GetSize(); ++j)
                {
                    // if a string within m_data matches a word within EXCLUDE_LIST
                    if ((*m_data)[j].first == (*it))
                    {
                        // then remove that common word 
                        m_data->RemoveAt(*it);
                    }
                }
            }
            cout << "All common words removed." << endl; 
        }
    }
    return; 
}


// Name: RemoveSingles
// Desc: Asks the user if they would like to remove words with a frequency of 1
//       Should use the overloaded [] NOTE: Don't forget m_data is a pointer!
// Preconditions: m_data is populated
// Postconditions: m_data will have no words with a frequency of 1
void Bar::RemoveSingles()
{
    // initalize userChoice and ask user if they want to remove common words 
    string userChoice;
    cout << "Would you like to remove all words with a frequency of 1?" << endl; 
    cin >> userChoice;
    // local constants for the user options 
    const string UPPERCASE_YES = "YES"; 
    const string LOWERCASE_YES = "yes"; 
    const string UPPERCASE_Y = "Y";
    const string LOWERCASE_Y = "y";
    // if the user indicates that they want to remove common words
    if ((userChoice == UPPERCASE_YES) or (userChoice == LOWERCASE_YES) or (userChoice == UPPERCASE_Y) or (userChoice == LOWERCASE_Y))
    {
        // check if m_data is empty first 
        if (m_data->GetSize() == 0) 
        {
            cout << "m_data is empty." << endl; 
        }

        else
        {
            int removeCount = 0; 
            // traverse the LL using normal for-loop and overloaded [ ]
            for (int i = 0; i < m_data->GetSize(); i++)
            {
                // check if each node has a freq of one
                if (((*m_data)[i]).second == 1)
                {
                    // remove that node from the LL by passing
                    // the string into RemoveAt()
                    m_data->RemoveAt((*m_data)[i].first);
                    // increment count of words removed 
                    ++removeCount; 
                    // reset the for-loop counter to 0 after removal
                    // since size is always changing
                    i = 0;
                }
            }
            // have another base case in case the first thing has a freq of 1
            if (((*m_data)[0]).second == 1)
            {
                m_data->RemoveAt((*m_data)[0].first);
            }   
            cout << removeCount << " words removed." << endl; 
        }
    }
    return; 
}

// Name: SortData
// Desc: Iterates through each items in m_data and inserts into
//       m_dataSorted using the frequency as the key (can use make_pair)
// Preconditions: m_data is populated
// Postconditions: m_dataSorted is populated and sorted based on frequency
void Bar::SortData()
{
    // traverse through m_data 
    for (int i = 0; i < m_data->GetSize(); i++)
    {
        // note to self: m_dataSorted is just a multi-map object that is 
        // not dynamically allocated 

        // pass the frequency of the string, THEN the actual string 
        // into m_dataSorted using make_pair and insert 
        m_dataSorted.insert(make_pair((*m_data)[i].second, (*m_data)[i].first));
    }    
}

// Name: DisplayBars
// Desc: Displays a bar chart for each item in m_dataSorted from highest
//       frequency (at the top) to lowest frequency (at the bottom) (iterate backwards)
// Preconditions:  m_dataSorted is populated
// Postconditions: Bar charts are displayed
void Bar::DisplayBars()
{
    // intiialize and use a reverse iterator to traverse the multi-map
    for (multimap<int, string>::reverse_iterator it = m_dataSorted.rbegin(); it != m_dataSorted.rend(); ++it)
    {
        // output the data 
        cout << setw(15) << it->second << ":"; 
        // then traverse based on the frequency of that data 
        for (int j = 0; j < it->first; j++)
        {
            // to output the barchart symbol 
            cout << barChar; 
        }
        cout << endl; 
    }
}

// Name: Export
// Desc: Asks the user what name the export file should be called
//       Iterates through m_dataSorted and exports to file
// Preconditions: m_dataSorted is populated
// Postconditions: New export file is created and populated with a formatted bar chart
void Bar::Export()
{
    // initialize var to get requested file name, and save that var
    string exportFileName; 
    cout << "What would you like to call the export file?" << endl; 
    cin >> exportFileName;
    // note to self: 
    // ofstream is for output or writing files
    // ifstream is for input or reading files

    ofstream exportData(exportFileName); // open the file 
    // traverse through the multi-map using iterator 
    // to create a new file in directory with the information from the multi-map 
    for (multimap<int, string>::iterator it = m_dataSorted.begin(); it != m_dataSorted.end(); ++it)
    {
        // export the data 
        exportData << setw(15) << it->second << ":"; 
        // then traverse based on the frequency of that data 
        for (int j = 0; j < it->first - 1; j++)
        {
            // to export the barchart symbol 
            exportData << barChar; 
        }
        // then export endline for cleanliness 
        exportData << endl; 
    }
    cout << "Output to export File: " << exportFileName << endl; 
}
