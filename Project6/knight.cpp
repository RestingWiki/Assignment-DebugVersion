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

    // Saving in progress...
    rescue = 1;



    // Get the file's prefix
    string knight_line,
           event_line,
           package_line;

    string ghost = "none";
    string merlin = "none";
    string god = "none";




        // Create a stream to read data
    ifstream istr;
    // Open the file
    istr.open(file_input);


    // Gather each line of data
    getline(istr, knight_line);
    getline(istr, event_line);
    getline(istr, package_line);

    istr.close();

    // Get the 3 lines of data
    
    {

        getData(file_input, knight_line, event_line, package_line);


    }
    


    // Read knight's data
    {


        readKnightData(knight_line, HP, level, remedy, maidenkiss, phoenixdown, rescue);

    }


        Charac k(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        

        // Read event's data
        int* arr;
        int  size = 0;      // Keep track the size of pointer array
        arr = readEventData(event_line,size);

    
        // Go to the kingdom
        package_Token(ghost, merlin, god, package_line);
        go_Adventure(arr,size,k,ghost,god,merlin);

        delete[] arr;
       

}

/***************************************
 *   Read the 3 lines of input         *
 ***************************************/
void getData(const string& name, string& knight, string& event, string& package){


    // Create a stream to read data
    fstream istr;
    //cout << "file to open:" << name << endl;
    // Open the file

    istr.open(name);

    if (istr.is_open())
    {
        //cout << "AAAAAAAAAAAAA" << endl;

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

        // Convert data to int respectively
        if ((stat.find("ghost") != string::npos) && sizeof(stat) > 0) ghost = stat;
        if ((stat.find("merlin") != string::npos) && sizeof(stat) > 0) merlin = stat;
        if ((stat.find("aclepius") != string::npos) && sizeof(stat) > 0) god = stat;
        wStart = line.find_first_not_of(delimeter, wEnd);
        count++;

        
    }
    
}
void debuff_Tracker(Charac& knight) {
    if (knight.forn_count == 3)
    {


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

    }
}
void  go_Adventure(int* arr, int size, Charac& knight, string& ghost1, string& god1, string& merlin1) {


    // (the first event corresponds to i = 1),
    int event_No = 1;
    
    // Have not save the princess yet!
    knight.rescue = -1;

    for (int i = 0; i < size; i++)    // Loop until finish all event
    {  


        if (knight.rescue == 0)
        {
            break;               
        }     

        // Check if the knight has finished all event
        if (i == size - 1)
        {

            knight.rescue = 1;

        }

        
        if (arr[i] == 0)                        // Bowser surrender
        {
            //TBD

            knight.rescue = 1;
            display(knight.HP, knight.level, knight.remedy, knight.maidenkiss, knight.phoenixdown, knight.rescue);
            break;
            
        }
        else if (1 <= arr[i] && arr[i] <= 5)    // Combat enemy
        {



            // Create an Enemy_Combat object
            Enemy_Combat enemy(arr[i], event_No);


            // Check the knight's level
            if (knight.level > enemy.levelO || knight.type == 2 || knight.type == 3)
            {

                knight.knight_LV_UP(1);


            }
            else if (knight.level == enemy.levelO)
            {

            }
            else
            {
                // Display text

                knight.HP -= enemy.deal_Damage();


                knight.try_Revive();
            }


            
        }
        else if (arr[i] == 6 || arr[i] == 7)    // Debuff enemy
        {
            // Check the knight's has already debuffed


            if (knight.form == 1 || knight.form == 2) 
            {

            }

            // Shaman
            else if (arr[i] == 6)
            {


                // Create a Shaman object
                Enemy_Debuff shaman(event_No,6);


                // Check the knight's level
                if (knight.level > shaman.levelO || knight.type == 2 || knight.type == 3)
                {

                    knight.knight_LV_UP(2);

                }
                else if (knight.level == shaman.levelO)
                {

                }
                else
                {
                    // Struck by debuff
                    if (knight.HP >= 5)
                    {
                        knight.og_MAX = knight.HP;
                        knight.HP = knight.HP / 5;
                    }
                    else
                        knight.HP = 1;



                    // Check for remedy
                    if (knight.remedy >= 1)
                    {

                        knight.remedy --;
                        knight.HP = knight.og_MAX;
                    }
                    else
                    {
                        knight.form = 2;                    
                    }


                }
            }

            // Siren
            else if (arr[i] == 7) {


                // Create a Siren object
                Enemy_Debuff siren(event_No, 7);


                // Check knight's level
                if (knight.level > siren.levelO || knight.type == 2 || knight.type == 3)
                {
                    knight.knight_LV_UP(2);

                }
                else if (knight.level == siren.levelO)
                {
                }
                else
                {
                    // Struck by debuff
                    knight.og_LVL = knight.level;
                    knight.level = 1;

                    // Check for maidenkiss
                    if (knight.maidenkiss >= 1)
                    {
                        knight.maidenkiss--;
                        knight.level = knight.og_LVL;
                    }
                    else
                    {
                        knight.form = 1;
                    }

  
                }
               
            }
        }
        else if (arr[i] == 11 || arr[i] == 12)  // Fib and Mario mushroom
        {
            // TBD

            // Mario mushroom
            if (arr[i] == 11)
            {
                Mush_Mario mario(knight);
            }
            else if (arr[i] == 12)
            {
                Mush_Fib fibonacci(knight);
            }
        }
        else if (arr[i] >= 130)                 // Ghost mushroom
        {
            //TBD
            Mush_Ghost ghosts(to_string( arr[i]),ghost1, knight);

        }
        else if (15 <= arr[i] && arr[i] <= 17)  // Pick up Item
        {
            // TBD
            Pickup_Item item(knight, arr[i]);

        }
        else if (arr[i] == 18 || arr[i] == 19)  // Merlin or Asclepius
        {
            // TBD

            // Merlin
            if (arr[i] == 18)
            {
                Merlin merlin(knight,merlin1);

            }

            if (arr[i] == 19)
            {
                God god(knight, god1);

            }
        }
        else if (arr[i] == 99)                  // King Bowser
        {
            //TBD
            if (knight.type == 3)
            {
                knight.knight_LV_UP(10);
            }
            else if (knight.type == 2 && knight.level >= 8)
            {
                knight.knight_LV_UP(10);
            }
            else if (knight.type == 1 && knight.level == 10)
            {
                knight.knight_LV_UP(10);
            }
            else
            {
                knight.rescue = 0;
                break;
            }
        }
        else
        {

            continue;
        }

        // Debuff time out
        debuff_Tracker(knight);
        
        display(knight.HP, knight.level, knight.remedy, knight.maidenkiss, knight.phoenixdown, knight.rescue);

        event_No++;

        
    }


  
}


