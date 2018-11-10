/*
 *
 * Marie-lou Yvette Memelink
 * Konrad Damian Paluch
 * "The Haunted Hospital"
 */

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/*
 * struct rooms
 * struct that holds info about every room
 * every cell contains:
 * three descriptions of the room
 * when entering, being able to interact, after interacting
 */
struct room{
    string sDescription1;
    string sDescription2;
    string sDescription3;
    string sOldMoves;
    string sNewMoves;
    bool bActionDone;
    bool bActionPossible;
    bool bAffectsItself;
    char cActionToDo;
    int iAffectedRoomRow;
    int iAffectedRoomCol;
};

/*
 * defineHospital
 * defining the rooms matrix from "RoomContent.txt"
 * loop for each room
 * template of the file in the file
 */
void defineHospital(room oRooms[3][3]){
    ifstream fMyFile("/Users/konradpaluch/CLionProjects/TheHauntedHospital/RoomContent.txt");

    for (int iRow = 0; iRow < 3; iRow++){
        for (int iCol = 0; iCol < 3; iCol++){
            getline(fMyFile, oRooms[iRow][iCol].sDescription1);
            getline(fMyFile, oRooms[iRow][iCol].sDescription2);
            getline(fMyFile, oRooms[iRow][iCol].sDescription3);
            getline(fMyFile, oRooms[iRow][iCol].sOldMoves);
            getline(fMyFile, oRooms[iRow][iCol].sNewMoves);
            fMyFile >> oRooms[iRow][iCol].bActionDone;
            fMyFile >> oRooms[iRow][iCol].bActionPossible;
            fMyFile >> oRooms[iRow][iCol].bAffectsItself;
            fMyFile >> oRooms[iRow][iCol].cActionToDo;
            fMyFile >> oRooms[iRow][iCol].iAffectedRoomRow;
            fMyFile >> oRooms[iRow][iCol].iAffectedRoomCol;
        }
    }
    fMyFile.close();
}

/*
 * menuDisplay
 * shows menu and possible choices to play or exit program
 * input: none
 * output: 1 for start game, 2 for exit
 */
int menuDisplay(){
    int iMenuDecision;
    cout << "Welcome to the Haunted Hospital detective." << endl;
    cout << "To choose an option, type in the number corresponding and press enter." << endl;
    cout << "1 Start game" << endl << "2 Exit" << endl;
    do {
        cin >> iMenuDecision;

        //check if it is an integer
        while (!cin){
            cin.clear();
            cin.ignore();
            cin >> iMenuDecision;
        }

    }
    while (iMenuDecision != 1 && iMenuDecision != 2);

    return iMenuDecision;
}

/*
 * showDescription function
 * input: matrix of rooms, players position
 * process: checks if bActionDone, if bActionPossible, shows according description
 * output: none
 */
void showDescription(room oRooms[3][3], int iPlayerRow, int iPlayerCol){
    if (oRooms[iPlayerRow][iPlayerCol].bActionDone){
        cout << oRooms[iPlayerRow][iPlayerCol].sDescription3 << endl;
    }
    else if (oRooms[iPlayerRow][iPlayerCol].bActionPossible){
        cout << oRooms[iPlayerRow][iPlayerCol].sDescription2;
    }
    else {
        cout << oRooms[iPlayerRow][iPlayerCol].sDescription1;
    }
}

/*
 * takeMake function
 * takes the player's input, checks if it is a possible action, if yes it modifies one of the bool in certain room,
 * if not an action, checks if possible movement, if not, asks for input again;
 */
void takeMake(room oRooms[3][3], int &iPlayerRow, int &iPlayerCol){
    char cDecision;
    cin >> cDecision;

    if ((cDecision == oRooms[iPlayerRow][iPlayerCol].cActionToDo) && (oRooms[iPlayerRow][iPlayerCol].bActionPossible)) {
        if (oRooms[iPlayerRow][iPlayerCol].bAffectsItself) {
            oRooms[iPlayerRow][iPlayerCol].bActionDone = true;
            oRooms[iPlayerRow][iPlayerCol].bActionPossible = false;
        }
        else {
            oRooms[oRooms[iPlayerRow][iPlayerCol].iAffectedRoomRow][oRooms[iPlayerRow][iPlayerCol].iAffectedRoomCol].bActionPossible = true;
            oRooms[iPlayerRow][iPlayerCol].bActionDone = true;
            oRooms[iPlayerRow][iPlayerCol].bActionPossible = false;
        }
    }
    else if (oRooms[iPlayerRow][iPlayerCol].bActionDone){
        if (oRooms[iPlayerRow][iPlayerCol].sNewMoves.find(cDecision) != oRooms[iPlayerRow][iPlayerCol].sNewMoves.npos){
            switch (cDecision) {
                case 'N':
                    iPlayerRow += 1;
                    break;
                case 'S':
                    iPlayerRow -= 1;
                    break;
                case 'W':
                    iPlayerCol -= 1;
                    break;
                case 'E':
                    iPlayerCol += 1;
                    break;
                default:
                    break;
            }
        }
    }
    else if (oRooms[iPlayerRow][iPlayerCol].sOldMoves.find(cDecision) != oRooms[iPlayerRow][iPlayerCol].sOldMoves.npos){
        switch (cDecision) {
            case 'N':
                iPlayerRow -= 1;
                break;
            case 'S':
                iPlayerRow += 1;
                break;
            case 'W':
                iPlayerCol -= 1;
                break;
            case 'E':
                iPlayerCol += 1;
                break;
            default:
                break;
        }
    }
    else {
        cin.clear();
        cin.ignore();
        cout << "This action is not possible. Please choose another one.";
    }
}

/*
 * game function
 * input: whole matrix
 * shows explanation, possible decisions, takes decision and alters players position
 */
void game(room oRooms[3][3]){
    cout << "In this game, you make decisions by typing in the first letter of the action you want to do, \nor the letter of the direction you want to go to. \n";
    int iPlayerRow = 2;
    int iPlayerCol = 1;

      while (!oRooms[0][0].bActionDone) {
          showDescription(oRooms, iPlayerRow, iPlayerCol);
          takeMake(oRooms, iPlayerRow, iPlayerCol);
          oRooms[0][0].bActionDone = true;
      }

    cout << "Congrats you have finished the game." << endl;
}


int main(){

    //int for choosing between running and exiting
    int iMenuDecision;

    //boolean that checks if the game should run or stop
    bool bRun = true;

    //matrix of story
    room oRooms[3][3];

    //defining our story
    defineHospital(oRooms);

    //menu loop
    while (bRun){

        iMenuDecision = menuDisplay();

        switch (iMenuDecision){
            //menu decision 1 means we want to play the game
            case 1:
                game(oRooms);
                break;

            //menu decision 2 means we want to exit program
            case 2:
                bRun = false;
                cout << "Thank you for playing the Haunted Hospital, \na game made by Marie-lou Memelink and Konrad Paluch";
                break;

            default:
                break;
        }
    }

    return 0;
}