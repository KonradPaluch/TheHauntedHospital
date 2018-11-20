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
    string sDesc1stEntrance;
    string sDescNextEntrances;
    string sDescActionPossible;
    string sDescAfterAction;
    string sDescActionDone;
    string sOldMoves;
    string sNewMoves;
    bool bActionDone;
    bool bActionPossible;
    bool bAlreadyVisited;
    bool bAffectsItself;
    char cActionToDo;
    int iAffectedRoomRow;
    int iAffectedRoomCol;
    int iAffectedRoomLevel;
};

/*
 * defineHospital
 * defining the rooms matrix from "RoomContent.txt"
 * loop for each room
 * template of the file in the file
 */
void defineHospital(room oRooms[3][3][3]){
    ifstream fMyFile("/Users/konradpaluch/CLionProjects/TheHauntedHospital/RoomContent.txt");
    int iLevel = 0;
    for (int iRow = 0; iRow < 3; iRow++) {
        for (int iCol = 0; iCol < 3; iCol++) {
            getline(fMyFile, oRooms[iRow][iCol][iLevel].sDesc1stEntrance);
            getline(fMyFile, oRooms[iRow][iCol][iLevel].sDescNextEntrances);
            getline(fMyFile, oRooms[iRow][iCol][iLevel].sDescActionPossible);
            getline(fMyFile, oRooms[iRow][iCol][iLevel].sDescAfterAction);
            getline(fMyFile, oRooms[iRow][iCol][iLevel].sDescActionDone);
            getline(fMyFile, oRooms[iRow][iCol][iLevel].sOldMoves);
            getline(fMyFile, oRooms[iRow][iCol][iLevel].sNewMoves);
            fMyFile >> oRooms[iRow][iCol][iLevel].bActionDone;
            fMyFile >> oRooms[iRow][iCol][iLevel].bActionPossible;
            fMyFile >> oRooms[iRow][iCol][iLevel].bAlreadyVisited;
            fMyFile >> oRooms[iRow][iCol][iLevel].bAffectsItself;
            fMyFile >> oRooms[iRow][iCol][iLevel].cActionToDo;
            fMyFile >> oRooms[iRow][iCol][iLevel].iAffectedRoomRow;
            fMyFile >> oRooms[iRow][iCol][iLevel].iAffectedRoomCol;
            fMyFile >> oRooms[iRow][iCol][iLevel].iAffectedRoomLevel;
        }
    }
    for (int iLevel = 1; iLevel < 3; iLevel++) {
        for (int iRow = 0; iRow < 2; iRow++) {
            for (int iCol = 0; iCol < 2; iCol++) {
                getline(fMyFile, oRooms[iRow][iCol][iLevel].sDesc1stEntrance);
                getline(fMyFile, oRooms[iRow][iCol][iLevel].sDescNextEntrances);
                getline(fMyFile, oRooms[iRow][iCol][iLevel].sDescActionPossible);
                getline(fMyFile, oRooms[iRow][iCol][iLevel].sDescAfterAction);
                getline(fMyFile, oRooms[iRow][iCol][iLevel].sDescActionDone);
                getline(fMyFile, oRooms[iRow][iCol][iLevel].sOldMoves);
                getline(fMyFile, oRooms[iRow][iCol][iLevel].sNewMoves);
                fMyFile >> oRooms[iRow][iCol][iLevel].bActionDone;
                fMyFile >> oRooms[iRow][iCol][iLevel].bActionPossible;
                fMyFile >> oRooms[iRow][iCol][iLevel].bAlreadyVisited;
                fMyFile >> oRooms[iRow][iCol][iLevel].bAffectsItself;
                fMyFile >> oRooms[iRow][iCol][iLevel].cActionToDo;
                fMyFile >> oRooms[iRow][iCol][iLevel].iAffectedRoomRow;
                fMyFile >> oRooms[iRow][iCol][iLevel].iAffectedRoomCol;
                fMyFile >> oRooms[iRow][iCol][iLevel].iAffectedRoomLevel;
            }
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
void showDescription(room oRooms[3][3][3], int iPlayerRow, int iPlayerCol, int iPlayerLevel){

    if (oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].bActionDone){
        cout << oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].sDescActionDone << endl;
        cout << "You can go " << oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].sNewMoves << "." << endl;
    }
    else if (oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].bActionPossible){
        cout << oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].sDescActionPossible << endl;
        cout << "You can go " << oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].sOldMoves << "." << endl;
    }
    else if (oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].bAlreadyVisited){
        cout << oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].sDescNextEntrances << endl;
        cout << "You can go " << oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].sOldMoves << "." << endl;
    }
    else {
        cout << oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].sDesc1stEntrance << endl;
        oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].bAlreadyVisited = true;
        cout << "You can go " << oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].sOldMoves << "." << endl;
    }
}

/*
 * takeMake function
 * takes the player's input, checks if it is a possible action, if yes it modifies one of the bool in certain room,
 * if not an action, checks if possible movement, if not, asks for input again;
 */
void takeMake(room oRooms[3][3][3], int &iPlayerRow, int &iPlayerCol, int &iPlayerLevel){
    char cDecision;
    cin.ignore();
    cin.clear();
    cin >> cDecision;
    //going up or down from the elevator
    if (iPlayerRow == 0 && iPlayerCol == 0 && iPlayerLevel == 0 && cDecision == 'D'){
        iPlayerLevel += 1;
    }
    else if (iPlayerRow == 0 && iPlayerCol == 0 && iPlayerLevel == 2 && cDecision == 'U'){
        iPlayerLevel -= 1;
    }
    else if (iPlayerRow == 0 && iPlayerCol == 0 && iPlayerLevel == 1){
        switch (cDecision){
            case 'U':
                iPlayerLevel -= 1;
                break;
            case 'D':
                iPlayerLevel += 1;
                break;
            default:
                break;
        }
    }
    if ((cDecision == oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].cActionToDo) && (oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].bActionPossible)) {
        if (oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].bAffectsItself) {
            oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].bActionDone = true;
            oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].bActionPossible = false;
        }
        else {
            oRooms[oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].iAffectedRoomRow][oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].iAffectedRoomCol][oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].iAffectedRoomLevel].bActionPossible = true;
            oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].bActionDone = true;
            oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].bActionPossible = false;
        }
        cout << oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].sDescAfterAction << endl;
    }
    else if (oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].bActionDone){
        if (oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].sNewMoves.find(cDecision) != oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].sNewMoves.npos){
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
    }
    else if (oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].sOldMoves.find(cDecision) != oRooms[iPlayerRow][iPlayerCol][iPlayerLevel].sOldMoves.npos){
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
        cout << "This action is not possible. Please choose another one." << endl;
    }
}

/*
 * endGame
 * function showing different endings depending on whether we saved a woman or not
 * input: bool of room 1 0 2
 * output: died, or you are sedated and lose memory
 */
void endGame(bool bSavedher){
    if (!bSavedher){
        cout << "You find yourself at the entrance to a laboratory. This laboratory however, seems to have tables with restraints. There are shelves on the wall with glass jars on them, holding different colors of human eyes. Bags of blood are hanging on the wall. \n\nIn the corner you see an opening in the floor, there is noise coming from it. Maybe it is someone who needs your help. You walk to the corner and notice that there are stairs going down. Slowly you get down the stairs not knowing what you will find when you get there. The first thing you see is a little girl, pale and restrained in the middle of the room. She looks at the wall with her lifeless eyes. She doesn’t react at all as you slowly walk into the room. You hear the noise again, footsteps from beyond the shelves behind the girl. You go forward, trying to make as little noise as possible. In front of you, you see the hospital’s director, and the man with a gun, pointed at the director. You take one step more, mesmerized by the scene, and you knock over a little jar. \nAs it breaks, the shooter looks at you. The director was just waiting for this moment. He leaps forward trying to hit the shooter in the head with a little knife he was hiding in his pocket. But the shooter is faster. He fires rapidly multiple times. The first bullet hits the head, next ones make the holes in director's entire body. As he shoots he keeps screaming “She was my little girl, how could you do it to her!!! My girl, my little girl!”. \n\nThen he stops and looks at you. You try to run away but his last bullet hits you right in your stomach. You collapse to the ground and see the shooter approaching you with the knife. “You were one of his assistants weren’t you? For monsters like you death is a too merciful punishment”, he whispers as he slits your throat open. The world turns dark.\n\n\n\n" << endl;
    }
    else {
        cout << "You find yourself at the entrance to a laboratory. This laboratory however, seems to have tables with restraints. There are shelves on the wall with glass jars on them, holding different colors of human eyes. Bags of blood are hanging on the wall. \n\nIn the corner you see an opening in the floor, there is noise coming from it. Maybe it is someone who needs your help. You walk to the corner and notice that there are stairs going down. Slowly you get down the stairs not knowing what you will find when you get there. The first thing you see is a little girl, pale and restrained in the middle of the room. She looks at the wall with her lifeless eyes. She doesn’t react at all as you slowly walk into the room. You hear the noise again, footsteps from beyond the shelves behind the girl. You go forward, trying to make as little noise as possible. In front of you, you see the hospital’s director, and the man with a gun, pointed at the director. You take one step more, mesmerized by the scene, and you knock over a little jar. \nAs it breaks, the shooter looks at you and starts aiming in your direction. \nHowever at the same moment, the woman you freed earlier runs into the room, screaming horribly. She runs straight at the shooter. The director was just waiting for this moment. He leaps forward and tries to hit the shooter in the head with the little knife he was hiding in his pocket. It all happens so fast. The woman get's hit in the head with a bullet, another one almost hits you as you throw yourself at the ground. The director reached the man and started hitting with the knife. \nYou try to stand up and run away, but then the director sees you, and turns to you with a sinister smile. He says “What an incident huh? You sure wouldn't like to remember it. Just as I wouldn't like you to remember it. But don't worry, you don't have to die.”. \nHe approaches you with the knife and as he is close to you, he hits you in the head with the gun's handle. You fall to the ground. He takes out a syringe and injects a medicine in your arm. ”No more memories, my dear, you kinda helped me her, so I'll help you too”. The world turns dark, as you see him approach the little girl and laugh quietly. \n\n\nYou wake up in a hospital bed. Your leg is hurting a bit, but it looks nicely patched up. A nurse enters the room. She says ”Oh how nice that you woke up mister, you had a bad accident. You may experience some bad memories, maybe even illusions, but don't worry, it will all pass”. She leaves the room and you look outside the window. It was all a dream right? It must've been a dream.\n\n" << endl;
    }
}

/*
 * game function
 * input: whole matrix
 * shows explanation, possible decisions, takes decision and alters players position
 */
void game(room oRooms[3][3][3]) {
    char cCheck;
    do {
        cin.clear();
        cout << "In this game, you make decisions by typing in the first letter of the action (in bold) you want to do (action will be in BOLD), \nor the letter of the direction you want to go to, like N S E W. \nLet's give it a try. Do you want to CONTINUE?\n\n";
        cin >> cCheck;
    }
    while (cCheck != 'C');

    int iPlayerRow = 1;
    int iPlayerCol = 0;
    int iPlayerLevel = 0;
    int iBleedingOut = 0;
    while (!oRooms[1][1][2].bActionDone) {
        //timer 
        if (iBleedingOut == 40) {
            oRooms[1][1][2].bActionDone = true;
        }
        showDescription(oRooms, iPlayerRow, iPlayerCol, iPlayerLevel);
        takeMake(oRooms, iPlayerRow, iPlayerCol, iPlayerLevel);
        if (!oRooms[0][2][0].bActionDone) {
            iBleedingOut++;
        }
        cout << endl;
    }
    if (iBleedingOut < 40) {
        endGame(oRooms[1][0][2].bActionDone);
    }
    else {
        cout << "You are bleeding to death. The walls are starting to get blurry as you try to hold on to them. \nYou fall to the ground and die.\n";
    }
}

int main(){
    //int for choosing between running and exiting
    int iMenuDecision;

    //boolean that checks if the game should run or stop
    bool bRun = true;

    //matrix of story
    room oRooms[3][3][3];

    //defining our story
    defineHospital(oRooms);

    //menu loop
    while (bRun) {

        iMenuDecision = menuDisplay();

        switch (iMenuDecision) {
            //menu decision 1 means we want to play the game
            case 1:
                game(oRooms);
                break;

                //menu decision 2 means we want to exit program
            case 2:
                bRun = false;
                cout << "Thank you for playing the Haunted Hospital, \na game made by Marie-lou Memelink and Konrad Paluch" << endl;
                break;
            default:
                break;
        }
    }
    cout << oRooms[0][1][0].sDescActionPossible;
    return 0;
}