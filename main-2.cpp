#include <iostream>
#include <string>
//acts like an array, can manipulate size unlike arrays
#include <vector>
//another list, similar to vectors, ntr: first one in is the first one out
#include <queue>
//stands for string stream
#include <sstream>
//allows us to work with files
#include <fstream>

using namespace std;

//this accesses the manually made function for turning strings into vectors.
//I found this code online and felt it would work perfect in my program.
vector<string> StringToVector(string, char separator);
//this accesses the other manually made function for turning vectors back into strings for output.
//I created this code by myself, following the code I found online for the above function.
string vectorToString(vector<string>, char separator);

int main() {
    //declaring the streams and variables for the program
    //ofstream means that I can open a file for the purpose of writing to it.
    ofstream writeToFile;
    //ifstream means that I can open a file for the purpose of reading to it, not writing.
    //fstream is the other stream for reading and writing both. Not just one or the other.
    ifstream readFromFile;
    string txtToWrite = " ";
    string txtFromFile = " ";
    //the boolean variables are for the switch like if statement later in the program
    bool inKeywords = false;
    bool inReserved = false;
    //set up a queue of vectors that are holding strings. This holds the first words of the txt file.
    queue<vector<string>> lines;
    //this holds a line per vector from the txt file separated by spaces.
    vector<string> vect;
    //keywords holds the first word plus definition for keywords for the ending output
    vector<vector<string>> keywords;
    //reserved hold the first word plus definition for the reserved words for the ending output
    vector<vector<string>> reserved;



    //              NOTES
    //ios::app : Append to the end of the file
    //ios::trunc : If the exists delete content
    //ios::in : Open file for reading
    //ios::out : Open file for writing
    //ios::ate : Open writing and move to the end of the file

    //ios_base::in for opening a file for reading
    readFromFile.open("CPP_Reference.txt", ios_base::in);

    //check if the file is open or not
    if(readFromFile.is_open())
    {
        //read from original CPP reference files
        while(readFromFile.good())
        {
            //store all the text in the variable txtFromFile
            getline(readFromFile, txtFromFile);

            //create a vector for each word in the txtFromFile and separate each word with a space and send it to
            //the String to Vector function
            vect = StringToVector(txtFromFile, ' ');

            //this will determine if there are any blank lines, and if there are, don't add them to the vector lines.
            //simply removing the blank lines from the file
            if(vect.empty())
            {
                //continue means to skip the rest of the while loop and begin the next iteration
                continue;
            }
            //add the line from the txt file separated by spaces into the lines queue, no blank lines.
	    lines.push(vect);
        }

        //once all the data is read and stored in the queue, close the file.
        readFromFile.close();

       //as a failsafe, execute as long as lines is not empty, or as long as lines doesn't encounter blank lines.
       while (!lines.empty())
        {
            //check if the front element, second column element equals "Keywords"
            //this will determine if the words following are keywords or reserved words.
            if (lines.front()[1] == "Keywords") {
                inKeywords = true;
                inReserved = false;
                //get rid of the first element to continue going through the loop.
                //the next element should be a word to defined followed by a dash, therefore not equalling "Keywords"
                lines.pop();
            }
            //similar to Keywords, this will check if we have reached the Reserved section of the document
            else if (lines.front()[1] == "Reserved") {
                inReserved = true;
                inKeywords = false;
                //just like keywords, pop the first element to continue going through the queue
                lines.pop();
            
            } else {
                //if in the keywords bracket, the variable inKeywords should be true, therefore we add the element to
                //the keywords vector
                if (inKeywords)
                    keywords.push_back(lines.front());
                //same as keywords, if reserved, the inReserved will be true and inKeywords false, therefore adding
                //the reserved word into the correct vector
                else if (inReserved)
                    reserved.push_back(lines.front());
                //pop the front element to progress going through the queue
                lines.pop();
            }
	    }
        //now that the data is read and placed in the correct lists, create a new file to write our data to
        //ios_base::out for the purpose of writing, not reading.
        writeToFile.open("CPP_Enhanced_Reference.txt", ios_base::out);

        //title of the new file, displays the vector size which is the count of how many words were defined.
        writeToFile << "C++ Keywords Defined = " << keywords.size() << endl << endl;

        //go through the vector and the text files there were once separated by spaces back into one full string
        for (int i = 0; i < keywords.size(); i++) {
            writeToFile << vectorToString(keywords[i], ' ') << endl;
        }
        //title of the reserved section, exactly like Keywords
        writeToFile << endl << "C++ Reserved Words Defined = " << reserved.size() << endl << endl;
        //go through the vector and the text files there were once separated by spaces back into one full string
        for (int i = 0; i < reserved.size(); i++) {
            writeToFile << vectorToString(reserved[i], ' ') << endl;
        }

        //once all the data was written to the file that was desired, close the file.
        writeToFile.close();
    } 
    
    else 
    {
        //in place in the case of the original file not opening.
        cout << "The file is not opening." << endl;
    }


    //end of program
    return 0;
}



vector<string> StringToVector(string theString, char separator){

    // Create a vector
    vector<string> vecsWords;

    // A stringstream object receives strings separated
    // by a space and then spits them out 1 by 1
    stringstream ss(theString);

    // Will temporarily hold each word in the string
    string sIndivStr;

    // While there are more words to extract keep
    // executing
    // getline takes strings from a stream of words stored
    // in the stream and each time it finds a blanks space
    // it stores the word proceeding the space in sIndivStr
    while(getline(ss, sIndivStr, separator))
    {
        // Put the string into a vector
        vecsWords.push_back(sIndivStr);
    }
    return vecsWords;
}


string vectorToString(vector<string> line, char separator) {

    // A stringstream object receives strings separated
    // by a space and then spits them out 1 by 1
    stringstream ss;

    //iterate through each word in the line and add it to the stringstream variable ss
    for (int i = 0; i < line.size() - 1; i++) {
	    ss << line[i] << separator;
    }
    ss << line.back();

    //return the stringstream variable with the string tag so it returns a string.
    return ss.str();
}
