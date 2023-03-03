#include "knight.h"



/*****************
 *  Display info *
 *****************/
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}


/*********************
 *   Main function   *
 *********************/
void adventureToKoopa(string file_input, int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown, int& rescue) {
    cout << "File input: " << file_input << endl;
    // Saving in progress...
    rescue = 1;

    // Get the file's prefix
    string prefix;
    string knight_line,
           event_line,
           package_line;

    string ghost = "none";
    string merlin = "none";
    string god = "none";

    getprefix(file_input, prefix);

    // Get the 3 lines of data
    {
        cout << "___________________________________" << endl;
        cout <<"Input file data:" << endl;
        getData(file_input, knight_line, event_line, package_line);

        cout << "Knight data: " << knight_line << endl;
        cout << "Event Lsit: "  <<  event_line << endl;
        cout << "Packge list: " << package_line << endl;
    }


    // Read knight's data
    {
        cout << "___________________________________" << endl;
        cout << "Retrieving knight's data!" << endl;

        readKnightData(knight_line, HP, level, remedy, maidenkiss, phoenixdown, rescue);

        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
    }


        Charac k(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        

        // Read event's data
        int* arr;
        int  size = 0;      // Keep track the size of pointer array
        arr = readEventData(event_line,size);

    
        // Go to the kingdom
        package_Token(ghost, merlin, god, package_line);
        go_Adventure(arr,size,k,prefix,ghost,god,merlin);

        delete[] arr;
       

}

/***************************************
 * Get the prefixes of the input files *                /// TO BE FIXED FOR GENERAL TEST CASES //
 ***************************************/
void getprefix(string file_input, string& prefix) {
    string::size_type wStart, wEnd;
    string delimeter = "_";

    // String tokenizer
    wStart = file_input.find_first_not_of(delimeter, 0);
    wEnd = file_input.find_first_of(delimeter, wStart);

    prefix = file_input.substr(wStart, wEnd - wStart);

    //prefix = file_input.substr(0, 3);
}

/***************************************
 *   Read the 3 lines of input         *
 ***************************************/
void getData(const string& name, string& knight, string& event, string& package){

    // Create a stream to read data
    ifstream istr;
    cout << "file to open:" << name << endl;
    // Open the file
    istr.open(name);

    if (istr.is_open())
    {
        cout << "AAAAAAAAAAAAA" << endl;

    }
    else
        cout << "Cant open file!";

    // Gather each line of data
    getline(istr, knight);
    getline(istr, event);
    getline(istr, package);
}

/***************************************
 *   Read the knight's initial data    *
 ***************************************/
void readKnightData(string line, int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown, int& rescue) {

  
    string stat;                    // Knight's stats
    string delimeter = " ";
    int count = 1;
    // String tokenizer
    string::size_type wStart, wEnd;

    wStart = line.find_first_not_of(delimeter, 0);
    while (wStart < line.npos) 
    {
        wEnd = line.find_first_of(delimeter, wStart);
        stat = line.substr(wStart, wEnd - wStart);

        // Convert data to int respectively
        if (count == 1) HP        = stoi(stat);
        if (count == 2) level     = stoi(stat);
        if (count == 3) remedy    = stoi(stat);
        if (count == 4) maidenkiss  = stoi(stat);
        if (count == 5) phoenixdown = stoi(stat);

        wStart = line.find_first_not_of(delimeter, wEnd);
        count++;
    }
}

/****************************************
 *           Read event data            *    
 ****************************************/
int* readEventData(string line, int& o_size) {

    cout << "___________________________________" << endl;
    cout << "Retrieving event data!" << endl;
    string event_i;                    // Knight's stats
    string delimeter = " ";
    int size = 0;
    // String tokenizer
    string::size_type wStart, wEnd;

    
    // Get the number of token
    {
        wStart = line.find_first_not_of(delimeter, 0);
        while (wStart < line.npos)
        {
            size++;
            wEnd   = line.find_first_of(delimeter, wStart);         
            wStart = line.find_first_not_of(delimeter, wEnd);
        }
    }
    cout <<"Size of the array: " << size << endl;

    // Create a pointer that points to an array of desired size
    int *arr1 = new int[size];
    
    // Fill the array with event code
    {
        size = 0;
        wStart = line.find_first_not_of(delimeter, 0);
        while (wStart < line.npos)
        {
            
            wEnd      = line.find_first_of(delimeter, wStart);
            event_i   = line.substr(wStart, wEnd - wStart);       // Retrieve that event code
            arr1[size] = stoi(event_i);                            // Copy the data as an integer to the  event array  
            wStart    = line.find_first_not_of(delimeter, wEnd);
            size++;
        }
    }

    // Test print the event
    {
        cout << "Retrieved array: ";
        for (int i = 0; i < size; i++) {
            cout << arr1[i] << " ";
        }
        cout << endl;
    }
    o_size = size;
    return arr1;
  

}

void package_Token(string& ghost, string& merlin, string& god, string& line) {
    
    string stat;                    // Knight's stats
    string delimeter = ",";
    int count = 1;
    // String tokenizer
    string::size_type wStart, wEnd;

    wStart = line.find_first_not_of(delimeter, 0);
    while (wStart < line.npos)
    {
        wEnd = line.find_first_of(delimeter, wStart);
        stat = line.substr(wStart, wEnd - wStart);
        cout << "STATTTTTTTTTTTTTTTTT " << stat << endl;
        cout << "count" << count << endl;
        // Convert data to int respectively
        if ((stat.find("ghost") != string::npos) && sizeof(stat) > 0) ghost = stat;
        if ((stat.find("merlin") != string::npos) && sizeof(stat) > 0) merlin = stat;
        if ((stat.find("aclepius") != string::npos) && sizeof(stat) > 0) god = stat;
        wStart = line.find_first_not_of(delimeter, wEnd);
        count++;

        
    }
    

    cout << "GHOST!" << ghost << endl;
    cout << "MERLIN" << merlin << endl;
    cout << "GOD" << god << endl;
}
void debuff_Tracker(Charac& knight) {
    if (knight.forn_count == 3)
    {
        cout << "You turned back to normal due to time out!" << endl;

        // From tiny to normal
        if (knight.form == 2)
        { 
            knight.HP = knight.HP * 5;
            knight.setHealth_toMax();
        }


        // From frog to normal
        if (knight.form == 1)
            knight.level = knight.og_LVL;

        knight.form = 0;
        knight.forn_count = 0;

        
    }
    if (knight.form != 0)
    {
        knight.forn_count++;
        cout << "Debuff no# " << knight.forn_count << endl;
    }
}
void  go_Adventure(int* arr, int size, Charac& knight, const string& prefix, string& ghost1, string& god1, string& merlin1) {
    cout << "Let's begin!" << endl;

    // (the first event corresponds to i = 1),
    int event_No = 1;
    
    // Have not save the princess yet!
    knight.rescue = -1;

    for (int i = 0; i < size; i++)    // Loop until finish all event
    {  


        if (knight.rescue == 0)
        {
            cout << "YOU CANNOT CONTINUE!" << endl;
            break;
               
        }
        cout << "--------------------------TURN#" << event_No << "----------------------------" << endl;


        // Debuff time out
        
        // Check event code and handle each event
       

        // Check if the knight has finished all event
        if (i == size)
        {
            cout << "YOU WON!";
            knight.rescue = 1;
            break;
        }

        
        if (arr[i] == 0)                        // Bowser surrender
        {
            //TBD
            cout << "Surrender!" << endl;
            knight.rescue = 1;
            break;
            
        }
        else if (1 <= arr[i] && arr[i] <= 5)    // Combat enemy
        {

            cout << "Combat Event" << endl;


            // Create an Enemy_Combat object
            Enemy_Combat enemy(arr[i], event_No);
            enemy.print();

            // Check the knight's level
            if (knight.level > enemy.levelO || knight.type == 2 || knight.type == 3)
            {
                cout << "\nVictory! You leveled up!" << endl;
                knight.knight_LV_UP(1);
                cout << "New stats:" << endl;
                    knight.print();
            }
            else if (knight.level == enemy.levelO)
            {
                cout << "\nDraw! You continue your jorney" << endl;
            }
            else
            {
                // Display text
                cout << "\nEnemy LV too hight! You took some damage!" << endl;
                knight.HP -= enemy.deal_Damage();
                cout << "New stats:" << endl;
                knight.print();
                knight.try_Revive();
            }


            
        }
        else if (arr[i] == 6 || arr[i] == 7)    // Debuff enemy
        {
            // Check the knight's has already debuffed


            cout <<"Debuff event!" << endl;

            if (knight.form == 1 || knight.form == 2) 
            {
                cout << "You got ignored!" << endl;
            }

            // Shaman
            else if (arr[i] == 6)
            {
                cout << "You met a Shaman!" << endl;

                // Create a Shaman object
                Enemy_Debuff shaman(event_No,6);
                shaman.print();

                // Check the knight's level
                if (knight.level > shaman.levelO || knight.type == 2 || knight.type == 3)
                {
                    cout << "\nVictory! You leveled up!" << endl;
                    knight.knight_LV_UP(2);
                    cout << "New stats:" << endl;
                    knight.print();
                }
                else if (knight.level == shaman.levelO)
                {
                    cout << "\nDraw! You continue your jorney" << endl;
                }
                else
                {
                    // Struck by debuff
                    knight.og_MAX = knight.HP;
                    if (knight.HP >= 5)
                        knight.HP = knight.HP / 5;
                    else
                        knight.HP = 1;

                    cout << "\n You shrunk!" << endl;

                    // Check for remedy
                    if (knight.remedy >= 1)
                    {
                        cout << "Remedy drank!" << endl;
                        knight.remedy --;
                        knight.HP = knight.og_MAX;
                    }
                    else
                    {
                        knight.form = 2;                    
                    }

                    knight.print();
                }
            }

            // Siren
            else if (arr[i] == 7) {

                cout << "You met a Siren Vajsh!" << endl;

                // Create a Siren object
                Enemy_Debuff siren(event_No, 7);
                siren.print();

                // Check knight's level
                if (knight.level > siren.levelO || knight.type == 2 || knight.type == 3)
                {
                    cout << "\nVictory! You leveled up!" << endl;
                    knight.knight_LV_UP(2);
                    cout << "New stats:" << endl;
                    knight.print();
                }
                else if (knight.level == siren.levelO)
                {
                    cout << "\nDraw! You continue your jorney" << endl;
                }
                else
                {
                    // Struck by debuff
                    knight.og_LVL = knight.level;
                    knight.level = 1;

                    // Check for maidenkiss
                    if (knight.maidenkiss >= 1)
                    {
                        cout << "Maidenkiss drank!" << endl;
                        knight.maidenkiss--;
                        knight.level = knight.og_LVL;
                    }
                    else
                    {
                        knight.form = 1;
                    }

                    knight.print();
                }
               
            }
        }
        else if (arr[i] == 11 || arr[i] == 12)  // Fib and Mario mushroom
        {
            // TBD
            cout << "Eat!" << endl;

            // Mario mushroom
            if (arr[i] == 11)
            {
                cout << "Mario Mushroom" << endl;
                Mush_Mario mario(knight);
            }
            else if (arr[i] == 12)
            {
                cout << "Fibonacci Mushroom" << endl;
                Mush_Fib fibonacci(knight);
            }
        }
        else if (arr[i] >= 130)                 // Ghost mushroom
        {
            //TBD
            cout << "Boo!" << endl;
            Mush_Ghost ghosts(to_string( arr[i]),ghost1, knight);
            knight.print();
        }
        else if (15 <= arr[i] && arr[i] <= 17)  // Pick up Item
        {
            // TBD
            cout << "yOINK!" << endl;
            Pickup_Item item(knight, arr[i]);
            knight.print();
        }
        else if (arr[i] == 18 || arr[i] == 19)  // Merlin or Asclepius
        {
            // TBD
            cout << "Bless!" << endl;

            // Merlin
            if (arr[i] == 18)
            {
                cout << "Merlin" << endl;
                Merlin merlin(knight,merlin1);
                knight.print();
            }

            if (arr[i] == 19)
            {
                cout << "God" << endl;
                God god(knight, god1);
                knight.print();
            }
        }
        else if (arr[i] == 99)                  // King Bowser
        {
            //TBD
            cout << "Boss!" << endl;
            if (knight.type == 3)
            {
                cout << "Arthur defeated BOWSER!" << endl;
                knight.knight_LV_UP(10);
            }
            else if (knight.type == 2 && knight.level >= 8)
            {
                cout << "Lancelot defeated BOWSER!" << endl;
                knight.knight_LV_UP(10);
            }
            else if (knight.type == 1 && knight.level == 10)
            {
                cout << "You defeated BOWSER!" << endl;
                knight.knight_LV_UP(10);
            }
            else
            {
                cout << "DEATH BY KING BOWSER!" << endl;
                knight.rescue = 0;
                break;
            }
        }
        else
        {
            cout << "Skip" << endl;
            continue;
        }

        debuff_Tracker(knight);
        event_No++;

        cout << "\n" << endl;
        
    }

    knight.print();
    cout << "This is the end of the program! " << endl;
    delete[] arr;
}


