#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "defns.h"
#include <string.h>

#define ANNUAL_STORM_LEN 5


using namespace std;

int findIndex(annual_storm* storm, int damage_property);
int countOccurences(annual_storm* storm, int area, int whichStorm);
void displayInfoAll(annual_storm* storm, int index);
void displayInfoDamage(annual_storm* storm, int index);
storm_event* read_storm_event(const string& filePath, int size);
string make_fileName(char* year, const char *extension);
int count_lines(const string& filePath);
fatality_event* read_fatality_event(const string& filePath, int size);
int insertionSort(annual_storm* storms, string sortBy, int size, int pos);

int main(int argc, char** argv)
{
    cout<< argc << "\n\n";
    //initializes the annual_storm struct and array
    annual_storm storms[atoi(argv[1])]; //Created the array to hold the annual storms, they'll be added here

    int year_count = 2; //Where the years are placed
    string file = "";

    for (int i = 0; i < argc - 2; i++) {
        storms[i].year = stoi(argv[year_count]);
        file = make_fileName(argv[year_count], "details-");
        int lines = count_lines(file);

        //There should be another struct right here, and we are going to need to input all of those things as well
        storms[i].storm_events = new storm_event;
        //storms[i].storm_events = read_storm_event(file, lines-1);

        storms[i].no_storms = lines - 1;
        file = "";
        file = make_fileName(argv[year_count], "fatalities-");
        lines = count_lines(file);
        storms[i].no_fatalities = lines - 1;

        //This will be the fatalities
        storms[i].fatality_events = new fatality_event;
        //storms[i].fatality_events = read_fatality_event(file, lines - 1);
        //This is to make sure that we're indexing the correct part of argv
        year_count++;
    }


    int currentFile = 0;
    //Iterates through every single file thrown into the thing.
    //int occurences = 0;
    //int damage;

    for (int i = 2; i < argc; i ++) {
        file = "";
        file = make_fileName(argv[i], "details-");

        storms[currentFile].storm_events = read_storm_event(file, storms[currentFile].no_storms);

        file = "";
        file = make_fileName(argv[i], "fatalities-");

        storms[currentFile].fatality_events = read_fatality_event(file, storms[currentFile].no_fatalities);

        //insertionSort(storms,"damage_type",atoi(argv[i]),"max", storms[currentFile].no_storms);
        //insertionSort(storms, "damage_property", storms[i].no_storms);
        //displayInfoAll(storms);
        //damage = findIndex(storms, 2500000);
        //occurences = countOccurences(storms, damage);
        //displayInfoDamage(storms, storms->no_storms-1);
        //for (int i = 0; i < storms[currentFile].no_storms; i++)
        //{
        //    cout<<storms[currentFile].storm_events->year <<"\t";
        //}
        currentFile++;
    }

    /*
    //Starting variables to store the options of the string that are inputed
    string saysSelect;
    string amountToDisplay;
    int yearToRead;
    string whatToRead;
    string sortToUse;
     */

    string queryInput;
    cin >> queryInput;
    string delimiter = "\n";
    string token = queryInput.substr(0,queryInput.find(delimiter)); // token is amount of inputs
    int num = stoi(token);
    string eachLine[num*5]; // holds all the words

    for (int i = 0; i < num * 5; i++) { //Gets all the words in an array
        cin >> eachLine[i];
        //cout << eachLine[i]; //select max 1950 damage_property insertion selectmin1950damage_propertyinsertionselect10alldamage_propertyinsertion
    }

    int current;
    string sortBy, sort;
    int year, spectrum, correctIndex;
    for (int i = 0; i < num; i++)
    {
        current = i*5; //Make sure we're indexing from the correct position as we go up, we increase the index by 5 to make sure we're looking at the second query
        //first we're going to determine what we are going to sort by
        sortBy = eachLine[current + 3]; //Stored in the 3rd position from select (select is at 0)
        sort =  eachLine[current + 4];

        if (eachLine[current + 2] == "all")
        {
            year = 1; //Making this a test case within the function that's going to read everything into the structures first.
        }
        else
            year = stoi(eachLine[current + 2]);

        if (eachLine[current + 1] == "max")
            spectrum = -1;
        else if (eachLine[current + 1] == "min")
            spectrum = -2;
        else
            spectrum = stoi(eachLine[current + 1]);

        //convert years to the proper index within the storms array

        int index =0;
        for (int i = 2; i < argc; i ++) //start at 2 because we don't want ./storm and the number of entries
        {
            //find the years given, and then assign them the index
            if (eachLine[current + 2] == argv[i])
            {
                index = i - 2;
            }
        }
        if (sort == "insertion")
        {
            //insertionSort(storms, sortBy, storms[0].no_storms, 0); //This is causing memory corruption
        }
        else if ( sort == "merge")
            //TODO implement merge sort
        {}
        //All data has been sorted
        //Step 2: find the min, max or the ith position given in the variable spectrum
        if (spectrum == -1) //Testing if it says max
        {
            correctIndex = storms[i].no_storms;
        }
        else if (spectrum == -2) //Testing if it says min
            correctIndex = 0;
        //The list is sorted from smallest to largest, therefore this will be correct

        //Step 3: Find the amount of occurences with that same value in the respective field
        //int amountOccurences = countOccurences(storms, storms->storm_events[correctIndex].damage_property, i);
        //cout<< amountOccurences;
        //displayInfoAll(storms);
    }

    return 0;
}

string make_fileName(char* year, const char *preface)
{
    char file[255];
    strcpy(file, "Data/");
    strcat(file, preface);
    strcat(file, year);
    strcat(file, ".csv");
    return file;
} //End of make_fileName

int count_lines(const string& filePath) {
    ifstream openFile(filePath.data());
    int count = 0;
    if(openFile.is_open() ) {
        string line;
        while (getline(openFile, line)) {
            count++;
        }
    }
    else {
        cout << "Error";
        return 0;
    }
    openFile.close();
    return count;

} //End of count lines

storm_event* read_storm_event(const string& filePath, int size)
{
    ifstream openFile(filePath.data());
    //Create the array to be returned

    //Array of storm events to return
    storm_event* stormArray = new storm_event[size];

    if(openFile.is_open() ){
        string line;
        int count = 0;
        while(getline(openFile, line)) {
            if (count > 0)
            {
                //At this point, the whole line of information is stored in one line
                //called line, and we turn that into a character array with the following command
                char str[255];
                strcpy(str, line.c_str());
                //cout << str << '\n';
                char *token = strtok(str, ",");
                // Keep printing tokens while one of the
                // delimiters present in *array[].
                int pos = 0;
                while (token != nullptr) {
                    string yeet(token);
		    switch (pos) {
		    case 0:
			stormArray[count].event_id = atoi(token);
			break;
		    case 1:
			strcpy(stormArray[count].state, token);
			break;
		    case 2:
			stormArray[count].year = atoi(token);
			break;
		    case 3:
			strcpy(stormArray[count].month_name, token);
			break;
		    case 4:
			strcpy(stormArray[count].event_type, token);
			break;
		    case 5:
			stormArray[count].cz_type = token[0];
			break;
		    case 6:
			strcpy(stormArray[count].cz_name, token);
			break;
		    case 7:
			stormArray[count].injuries_direct = atoi(token);
			break;
		    case 8:
			stormArray[count].injuries_indirect = atoi(token);
			break;
		    case 9:
			stormArray[count].deaths_direct = atoi(token);
			break;
		    case 10:
			stormArray[count].deaths_indirect = atoi(token);
			break;
			case 11:
			    if (yeet.back() == 'K') {
                    double newToken = 1000*stod(token);
                    stormArray[count].damage_property = (int)newToken;
                }
			    else if (yeet.back() == 'M') {
                    double newToken = stod(token)*1000000;
                    stormArray[count].damage_property = (int)newToken;
                }
			    else
			        stormArray[count].damage_property = atoi(token);
			break;
		    case 12:
                if (yeet.back() == 'K') {
                    double newToken = 1000*stod(token);
                    stormArray[count].damage_crops = (int)newToken;
                }
                else if (yeet.back() == 'M') {
                    double newToken = stod(token)*1000000;
                    stormArray[count].damage_crops = (int)newToken;
                }
                else
                    stormArray[count].damage_crops = atoi(token);
			break;
		    }

                    if (pos == 12) {
                        pos = 0;
                    } else
                        pos++;

                    token = strtok(nullptr, ","); //Go to the next thing
                } //End of while
            }//end of if
            //cout <<'\n';
            count++;

        } //End of while
        openFile.close();
    }//end of If

    return stormArray;

}//End of read_storm_event

fatality_event* read_fatality_event(const string& filePath, int size)
{
    ifstream openFile(filePath.data());
    //Create the array to be returned

    //Array of storm events to return
    fatality_event* fatalityArray = new fatality_event[size];

    if(openFile.is_open() ){
        string line;
        int count = 0;
        while(getline(openFile, line)) {
            if (count > 0)
            {
                //At this point, the whole line of information is stored in one line
                //called line, and we turn that into a character array with the following command
                char str[255];
                strcpy(str, line.c_str());
                //cout << str << '\n';
                char *token = strtok(str, ",");
                // Keep printing tokens while one of the
                // delimiters present in *array[].
                int pos = 0;
                while (token != nullptr) {
		    switch (pos) {
		    case 0:
			fatalityArray[count].event_id = atoi(token);
			break;
		    case 1:
			fatalityArray[count].fatality_type = token[0];
			break;
		    case 2:
			strcpy(fatalityArray[count].fatality_date, token);
			break;
			case 3:
			    fatalityArray[count].fatality_age = -1;
			break;
			case 4:
		        fatalityArray[count].fatality_sex = 'a';
			break;
		    case 5:
		        strcpy(fatalityArray[count].fatality_location, token);
			break;
		    }

                    if (pos == 5) {
                        pos = 0;
                    } else
                        pos++;

                    token = strtok(nullptr, ","); //Go to the next thing
                } //End of while
            }//end of if
            count++;

        } //End of while
        openFile.close();
    }//end of If

    return fatalityArray;

}//End of read_fatality_event

int insertionSort(annual_storm* storms, string sortBy, int size, int pos)
{

    //if (sortBy == "damage_property")
    //{
    int i, key, j;
    for (i = 1; i < size; i++) {
        key = storms[pos].storm_events[i].damage_property;
        j = i - 1;

        while (j >= 0 && storms[pos].storm_events[j].damage_property > key) {
            storms[pos].storm_events[j + 1] = storms[pos].storm_events[j];
            j = j - 1;
        }
        storms[pos].storm_events[j + 1].damage_property = key;
    }
    //}
    /*
    else if (sortBy == "damage_crops")
    {
        int i, key, j;
        for (i = 1; i < size; i++) {
            key = storms->storm_events[i].damage_crops;
            j = i - 1;
            while (j >= 0 && storms->storm_events[j].damage_crops > key) {
                storms->storm_events[j + 1] = storms->storm_events[j];
                j = j - 1;
            }
            storms->storm_events[j + 1].damage_crops = key;
        }
    }
     */
    /*
    else if (type == "fatality")
    {
        int i, key, j;
        for (i = 1; i < size; i++) {
            key = storms->storm_events[i].damage_crops;
            j = i - 1;
            while (j >= 0 && storms->storm_events[j].damage_crops > key) {
                storms->storm_events[j + 1] = storms->storm_events[j];
                j = j - 1;
            }
            storms->storm_events[j + 1].damage_crops = key;
        }
    }
     */
    return 1;
} //End of insertion sort

void displayInfoAll(annual_storm* storm, int index)
{
    for (int i = 0; i < storm->no_storms; i++)
    {
        cout<< storm[index].storm_events[i].event_id<<'\t';
        cout<< storm[index].storm_events[i].state<<'\t';
        cout<< storm[index].storm_events[i].year<<'\t';
        cout<< storm[index].storm_events[i].month_name<<'\t';
        cout<< storm[index].storm_events[i].event_type<<'\t';
        cout<< storm[index].storm_events[i].cz_type<<'\t';
        cout<< storm[index].storm_events[i].cz_name<<'\t';
        cout<< storm[index].storm_events[i].injuries_direct<<'\t';
        cout<< storm[index].storm_events[i].injuries_indirect<<'\t';
        cout<< storm[index].storm_events[i].deaths_direct<<'\t';
        cout<< storm[index].storm_events[i].deaths_indirect<<'\t';
        cout<< storm[index].storm_events[i].damage_property<<'\t';
        cout<< storm[index].storm_events[i].damage_crops<<'\n';
    }
} //End of displayInfoAll

void displayInfoDamage(annual_storm* storm, int index) {
    int num = index - 4;
    for (int i = index; i > num; i--) {
        cout << "\t" << storm->storm_events[i].year<<"\n";
        cout << "\t\tEvent ID: " << storm->storm_events[i].event_id << '\n';
        cout << "\t\tState: " << storm->storm_events[i].state << '\n';
        cout << "\t\tYear: " << storm->storm_events[i].year << '\n';
        cout << "\t\tMonth: " << storm->storm_events[i].month_name << '\n';
        cout << "\t\tEvent Type: " << storm->storm_events[i].event_type << '\n';
        cout << "\t\tCounty/Parish/Marine: " << storm->storm_events[i].cz_type << '\n';
        cout << "\t\tCounty/Parish/Marine Name:" << storm->storm_events[i].cz_name << '\n';
        cout << "\t\tInjuries Direct: " << storm->storm_events[i].injuries_direct << '\n';
        cout << "\t\tInjuries Indirect: " << storm->storm_events[i].injuries_indirect << '\n';
        cout << "\t\tDeaths Direct: " << storm->storm_events[i].deaths_direct << '\n';
        cout << "\t\tDeaths Indirect: " << storm->storm_events[i].deaths_indirect << '\n';
        cout << "\t\tDamage to Property: " << storm->storm_events[i].damage_property << '\n';
        cout << "\t\tDamage to Crops: " << storm->storm_events[i].damage_crops << "\n\n";
    }

} //End of displayInfoDamage

int countOccurences(annual_storm* storm, int area, int whichStorm)
{
    int count = 0;
    for (int i = 0; i < storm[whichStorm].no_storms; i++)
    {
        if (storm->storm_events[i].damage_property == storm->storm_events[area].damage_property)
        {
            count ++;
        }
    }
    return count;
} //End of countOccurences

int findIndex(annual_storm* storm, int damage_property)
{
    for (int i =0; i < storm->no_storms; i ++)
    {
        if (storm->storm_events[i].damage_property == damage_property)
            return i;
    }
    return 0;
} //End of findIndex
