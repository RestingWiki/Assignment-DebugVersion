#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"




void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void getprefix(string file_input, string& prefix);
void getData(const string& prefix, string& knight, string& event, string& package);

void readKnightData(string file_input, int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown, int& rescue);
int* readEventData(string file_input, int &o_size);


class Charac {
public:
    int init = 0;
    int& HP = init;
    int& level = init;
    int& remedy = init;
    int& maidenkiss = init;
    int& phoenixdown = init;
    int& rescue = init;

    int form   = 0;                // 0 for normal, 1 for frog, 2 for tiny
    int forn_count = 0;
    int type   = 1;                 // 1 = round table, 2 = lancelot, 3 = arthur
    int og_MAX = 0;                 // Old max HP

    // Merlin and The God
    int merlin_Count = 0;
    int god_Count    = 0;

    // Siren
    int og_LVL = 0;                 // Old max LVL


    // Constructor
    Charac(int& health, int& lvl, int& rem, int& maid, int& phoenix, int& res) :
        HP(health), level(lvl), remedy(rem), maidenkiss(maid), phoenixdown(phoenix), rescue(res)
    {
        og_MAX = HP;
        cout << "Class succes" << endl;
        setType();
        set_ItemLimit();
    };
    Charac()
    {
    };
    
    // Supporting function
    void setStats(int& health, int& lvl, int& rem, int& maid, int& phoenix, int& res)
    {
        HP = health;
        level = lvl;
        remedy = rem;
        maidenkiss = maid;
        phoenixdown = phoenix;
        rescue = res;
    };
    void setHealth_toMax() {
  
        if (HP > og_MAX)
            HP = og_MAX;
    }               // Set HP to max after limit reached                
    void setLevel_toMax() {
        if (level > 10)
            level = 10;
    }
    void knight_LV_UP(int lvl) {
        level += lvl;
        setLevel_toMax();
    }
    // Print
    void print() {
        
        cout << "HP=" << HP
            << ", level=" << level
            << ", remedy=" << remedy
            << ", maidenkiss=" << maidenkiss
            << ", phoenixdown=" << phoenixdown
            << ", rescue=" << rescue
            << ", type=" << type 
            << ",OG_MAX="<< og_MAX << endl;
            
    };
    void try_Revive() {
        if (HP <= 0)
        {
            // Check for phoenix
            if (phoenixdown > 0)
            {
                cout << "Revived!" << endl;
                phoenixdown--;
                HP = og_MAX;
                form = 0;
                forn_count = 0;
                print();
            }
            else
            {
                cout << "You DIED!" << endl;
                rescue = 0;
            }
        }
    }
    void set_ItemLimit()
    {
        if (level > 10)
            level = 10;
        if (remedy > 99)
            remedy = 99;
        if (maidenkiss > 99)
            maidenkiss = 99;
        if (phoenixdown > 99)
            phoenixdown = 99;
    }

private:
    void setType() {
        isPrime(HP);
    }
    void isPrime(int num) {
        if (num <= 1)
            type = 1;               // Round table knight
        else if (num == 2)
            type = 2;               // Lancelot
        else if ((2 < num) && (num < 999))         // Check prime number 
        {
            for (int i = 2; i <= num / 2; i++)
            {
                if ((num % i) == 0)
                {
                    type = 1;
                    break;
                }

                type = 2;
            }
        }
        else if (num == 999)
            type = 3;

    }

};

class Enemy_Combat {
public: 
    int levelO = 1;
private:
    int type = 1;               // Enemy type, default is 1 aka MadBear  
    int event_No = 1;
    double b_Damage = 0;
    string enemy_Name = "None";
public:

    // Mutators
    void set_CombatType(const int code) {
        type = code;
    };  // Set combat type

    // Accessor


    // Constructor
    Enemy_Combat() {
    };
    Enemy_Combat(const int code, const int eve_No): type(code), event_No(eve_No) {
        set_Name(type);
        set_BaseDmg();
        calc_Level();
    }

    // Print function                                                <--------------------------------------------------------------------------
    print() {
        cout << "Enemy type: " << type << "\tName: "<< enemy_Name << "\tBase damage: " << b_Damage << endl;
        cout << "Enemy LV: " << levelO <<  "\tDamage: " << deal_Damage() << endl;
    }

    // Damage dealt
    double deal_Damage() {
        double dam = b_Damage*levelO*10;
        return dam;
    }
private:
    // Set enemy name to keep track
    void set_Name(const int code) {

        switch (code)
        {
        default:
            break;
        case 1:
        {
            enemy_Name = "MadBear";
            break;
        }
        case 2:
        {
            enemy_Name = "Bandit";
            break;
        }
        case 3:
        {
            enemy_Name = "LordLupin";
            break;
        }
        case 4:
        {
            enemy_Name = "Elf";
        }
        case 5:
        {
            enemy_Name = "Troll";
            break;
        }
        }

    }

    // Set enemy base damage
    void set_BaseDmg() {
        switch (type)
        {
        default:
            break;
        case 1:
        {
            b_Damage = 1.;
            break;
        }
        case 2:
        {
            b_Damage = 1.5;
            break;
        }
        case 3:
        {
            b_Damage = 4.5;
            break;
        }
        case 4:
        {
            b_Damage = 7.5;
            break;
        }
        case 5:
        {
            b_Damage = 9.5;
            break;
        }
        }

    }

    // Calculate "levelO"
    void calc_Level() {
        int b = event_No % 10;
        cout << "Event no: " << event_No << endl;
        cout << "(event_No > 6 ? (b > 5 ?b : 5) : b) = " << (event_No > 6 ? (b > 5 ? : 5) : b) << endl;
        levelO = (event_No > 6 ? (b > 5 ?b : 5) : b);
    }
};
class Enemy_Debuff {
public:
    int levelO = 1;
private:
    int event_No = 1;
    int type = 0;
    string enemy_Name = "Debuff_Enemy";
public:
    // Constructor
    Enemy_Debuff(const int eve_No, const int code) : event_No(eve_No) , type(code)
    { 
        calc_Level();
        setName();
    }

    // Print function                               <--------------------------------------------------------------------------
    void print() {
        cout << "Enemy type: " << "Debuff" << "\tName " << enemy_Name << endl;
        cout << "Enemy LV: " << levelO << endl;
    }

private:
    // Calculate "levelO"
    void calc_Level() {
        int b = event_No % 10;
        levelO = event_No > 6 ? (b > 5 ? : 5) : b;
    }
    // Set name based off event code
    void setName() {
        if (type == 6)
            enemy_Name = "Shaman";
        if (type == 7)
            enemy_Name = "Siren Vajsh";
    }
};
class Mush_Mario {
private:
    int bonus_HP;
    int s1 = 0;
    int n1;
public:

    // Constructor
    Mush_Mario(Charac& knight) {

        // Calculate sum
        calc_n1(knight);
        calc_s1();
        add_HP(knight);
        
    }
private:
    void calc_n1(Charac& knight){
        n1 = ((knight.level + knight.phoenixdown) % 5 + 1) * 3;
    }
    void calc_s1() {
        for (int i = 0; i < n1; i++) {
            s1 += 99 - i * 2;
        }
    }
    void add_HP(Charac& knight) {

        bonus_HP = (s1 % 100);
        cout << "Bonus HP=" << bonus_HP << endl;

        knight.HP += bonus_HP;
        cout << "New HP= " << knight.HP << endl;
        knight.HP++;
        // Increase knight's hp to prime
        while (  !isPrime(knight.HP)   )
        {
            cout << "Increasing to prime" << endl;
            knight.HP++;
        }


        // Set knight's HP to original max vlaue
        knight.setHealth_toMax();

        // Print after eating
        cout << "After eating Mario Mushroom. The knight new stats are:" << endl;
        knight.print();
    }

    // Check for prime HP
    bool isPrime(int num) {
        if (num <= 1)
            return false;
        else if (num == 2)
            return true;
        else
        {
            for (int i = 2; i <= num / 2; i++)
            {
                if (num % i == 0) 
                {
                    return false;
                }
            }
        }

        return true;
    }
};
class Mush_Fib {
private:
        int first = 1;
        int second = 1;
public: 

    // Constructor
    Mush_Fib(Charac& knight) {
        int temp;
        if (knight.HP != 1)
        { 
         while (second < knight.HP)
            {
                // 1 1 2
                temp = second;
                second = first + second;
                first = temp;
            }

            cout << "First:  " << first << endl;
            cout << "Second: " << second << endl;
            cout << "HP:     " << knight.HP << endl;

            // Drop the knight's HP to the nearest fibonacci number
            knight.HP = first;
            knight.print();

        }
    }
    
};
class Mush_Ghost {
private:
    // Cluster  eg : 133214
    string cluster;

    // File name
    string fName;

    // Mushroom array;
    int* arr_Mush;
    int size;
    // File's data
    string f_line1 = "0";
    string f_line2 = "0";
    int arr_Num[100];
    int arr_NumSize = 0;
    int arr_NumEX[100];
    int mush_no = 0;

public:
    // Constructor
    Mush_Ghost(string token, string fname, Charac& knight) : cluster(token), fName(fname)
    {
        open_MushGhost(knight);
    }

private:


    /****************
     * GENERAL USES *
     ****************/
    // Open the mush ghost file
    void open_MushGhost(Charac& knight) {


        // Create a stream to read file
        fstream istr;
        istr.open(fName);

        // Check if the file has been opened
        if (istr.is_open())
        {
            cout << "File: " << fName << " has been succesfully opened!" << endl;
            ExtractData(istr);
            tokenizer();
            extractMushroom();
            convertToArray(knight);               

        }
        else
        {
            cout << "File: " << fName << " CAN'T BE opened!" << endl;
        }
    }
    // Extract the mushroom number;
    void extractMushroom()
    {
        cout << "Old cluster:" << cluster << endl;
        cluster = cluster.substr(2, cluster.length() - 2);
        cout << "New cluster: " << cluster << endl;
    }
    void convertToArray(Charac& knight) {

         size = cluster.size();
        // Create a pointer that points to an array of string
        arr_Mush = new int[size];


        // Move each number to the array
        cout << "Array content:\t";
        for (int i = 0; i < size; i++)
        {
            arr_Mush[i] = stoi(cluster.substr(i, 1));
        }

        // Handle each mushroom cases
        cout << endl;   
        handleMushroom(knight);

        // Delete array
        delete[] arr_Mush;
    }
    // Extract Data from file
    void ExtractData(fstream& istr) {
        getline(istr, f_line1);
        getline(istr, f_line2);



        // Set the array
        arr_NumSize = stoi(f_line1);
        cout << arr_NumSize << endl;
        cout << f_line2 << endl;

        // Tokenize the second line to fill num_array
    }
    // Tokenize the second lize
    void tokenizer() {

        string::size_type wEnd, wStart;
        string delimeter = ",";
        wStart = f_line2.find_first_not_of(delimeter,0);

        cout << "Extracted from "<< fName << endl;
        for (int i = 0; i < arr_NumSize; i++)
        {
            wEnd = f_line2.find_first_of(delimeter, wStart);
            arr_Num[i] = stoi(f_line2.substr(wStart, wEnd - wStart));
            wStart = f_line2.find_first_not_of(delimeter, wEnd);


            // Print
            
            cout << arr_Num[i] << "\t";
            
        }
        cout << endl;
    }


    /***************
     *  Mushroom 2 *
     ***************/

    //  Variables
    int pos_peak = 0;
    int mtx = -2;
    int mti = -3;
 
    // Find the peak position
    void find_PosPeak(int& pos_peak)        
    {
        if (arr_NumSize > 1)
        { 
            for (int i = 1; i < arr_NumSize; i++)
        {
            if( arr_Num[pos_peak] <= arr_Num[i])
            { 
                
                pos_peak = i;

            }
            // Move the peak to the border if necessary
            if (arr_Num[pos_peak] == arr_Num[pos_peak - 1]&& pos_peak != (arr_NumSize -1))
                pos_peak = pos_peak -1;
            
        }
        }
        else if (arr_NumSize == 1)
        {
            pos_peak = 0;
        }



    }

    // Check increment
    bool check_Increment()
    {
        // If the peak is on one of the 2 end of the array 
        if (pos_peak == 0 || pos_peak == (arr_NumSize - 1))
        {
            cout << "Peak is at border!" << endl;
            if (!check_Repetition())
            {
                cout << "Not strict increment!" << endl;
                return false;
            }
            else
            {
                if (!check_Increment_Sec(pos_peak))
                {
                    return false;
                }
            }
            // Checking increment from 0 to before post peak

        }
        else
        {
            // Check repetition from 0 to post_peak  5 4 3 6 *6
            if (!check_Repetition(pos_peak,0))
            {
                cout << "Not strict increment!" << endl;
                return false;
            }
            // Check increment from 0 to before post peak;
            else
            {
                if (!check_Increment_Sec(pos_peak))
                {
                    return false;
                }
            }
                

        }

        cout << "Strict Incremnt Reached!!!!!!!!!" << endl;
            return true;
    }
    // Check repetition in a section
    bool check_Repetition() {
        
        // Check for even elements
        for (int i = 0; i < arr_NumSize; i++)
        {
            for (int j = i+1; j < arr_NumSize ; j++)
            {                
                if (arr_Num[i] == arr_Num[j])
                {
                   
                    // Checking even element
                    cout << arr_Num[i] << " = " << arr_Num[j] << endl;
                    return false;
                }
            }
        }
            return true;
    }
    bool check_Repetition(const int& pos_peak, int choice)                  // 0 for increment section, 1 for decrement setion
    {

        if (choice == 0)
        { 
            for (int i = 0; i <= pos_peak; i++)
            {
                for (int j = i + 1; j <= pos_peak; j++)
                {
                    if (arr_Num[i] == arr_Num[j])
                    {
                        // Checking repeat element
                        cout << arr_Num[i] << " = " << arr_Num[j] << endl;
                        return false;
                    }
                }
            }
        }

        else if (choice == 1)
        {
            for (int i = pos_peak; i < arr_NumSize-1; i++)
            {
                for (int j = i + 1; j < arr_NumSize; j++)
                {
                    if (arr_Num[i] == arr_Num[j])
                    {
                        // Checking repeat element
                        cout << arr_Num[i] << " = " << arr_Num[j] << endl;
                        return false;
                    }
                }
            }
        }
        return true;
    }

    // Check increment in a section
    bool check_Increment_Sec(const int& post_peak)
    {
        cout << "Checking for increment in the first secsion!" << endl;
        for (int i = 1; i < pos_peak; i++)
        {
            if (arr_Num[i - 1] >= arr_Num[i])
            {
                cout << "Not strict increment IN SECTIONS!" << endl;
                return false;
            }

        }

        return true;
    }


    // Check decrement     PS: don't care about the border of the array since  "check_Increment" has covered that case!!!!
    bool check_Decrement() {
        // Check repetition from post_peak to the end of the array
        if (!check_Repetition(pos_peak, 1))
        {
            cout << "Not strict decrement!" << endl;
            return false;
        }
        // Check decrement from post peak to the end of the array;
        else
        {
            if (!check_Decrement_Sec(pos_peak))
            {
                return false;
            }
        }


        cout << "Strict Decremnt Reached!!!!!!!!!" << endl;
        return true;
    }
    // Check decrement in a section
    bool check_Decrement_Sec(const int& post_peak) {
        cout << "Checking for decrement in the second secsion!" << endl;
        for (int i = post_peak +1; i < arr_NumSize; i++)
        {
            if (arr_Num[i - 1] <= arr_Num[i])
            {
                cout << "Not strict decrement IN SECTIONS!" << endl;
                return false;
            }

        }

        return true;
    }


    /***************
     *  Mushroom 3 *
     ***************/


    // Variables
    int maxi2 = 0;
    int mini2 = 0;

    // Transform the array and move it into a different array
    void transformation(){
        for (int i = 0; i < arr_NumSize; i++)
        {

            // Transform each element and put it into new array
            if (arr_Num[i] < 0)
            {

                arr_NumEX[i] = (17 * -arr_Num[i] + 9) % 257;
            }
            else
             
                arr_NumEX[i] = (17 * arr_Num[i] + 9) % 257;
            
            


           
            cout << "[" << arr_NumEX[i] << "]\t";

        }
        cout << endl;
    }

    // Find mixi2 and mini2
    void findMaxMini() {
        for (int i = 1; i < arr_NumSize; i++)
        {
            if (arr_NumEX[i] > arr_NumEX[maxi2])
                maxi2 = i;
            if (arr_NumEX[i] < arr_NumEX[mini2])
                mini2 = i;
        }

        cout << "Maxi2 = " << maxi2 << "\tMini2 = " << mini2 << endl;
    }


    /***************
     *  Mushroom 4 *
     ***************/

    // Variables
    int max_x3 = -5;
    int max_i3 = -7;
    int largest_Index = 0;

    // Functions
    void find_2ndLargerst() {

        // Array has one or less elements
        if (arr_NumSize == 0 || arr_NumSize == 1)
        {
        }
        // Array has only 2 elements
        else if (arr_NumSize == 2)
        {
            // 2 elements have the same value
            if (arr_NumEX[0] == arr_NumEX[1])
            {
            }
            else if (arr_NumEX[0] > arr_NumEX[1])
            {
                max_x3 = arr_NumEX[1];
                max_i3 = 1;
            }
            else
            {
                max_x3 = arr_NumEX[0];
                max_i3 = 0;
            }
        }
        // Array has 3 or more element
        else
        {
            // 3 elements has the same value
            if (arr_NumEX[0] == arr_NumEX[1] && arr_NumEX[1] == arr_NumEX[2])
            {
                    
            }
            else
            {
                int smallest, largest;

                smallest = min(arr_NumEX[0], arr_NumEX[1]);
                largest = max(arr_NumEX[0], arr_NumEX[1]);
                largest = min(smallest, arr_NumEX[2]);
                smallest = max(largest, arr_NumEX[2]);



                // Find the 1st 3 element of the array
                for (int i = 0; i < 3; i++)
                {
                    cout << arr_NumEX[i] << "\t";
                    
                }
                cout << endl;

                // Find the second largest and its position in the array
                for (int i = 0; i < 3; i++)
                {
                    if (!((arr_NumEX[i] != smallest) &&  (arr_NumEX[i] != largest)))
                    {
                        max_i3 = i;
                        max_x3 = arr_NumEX[i];
                    }
                }

            }

        }
    }



    /*******************************************
     **     Handle each  Ghost mushroom code  **
     *******************************************/
    void handleMushroom(Charac&  knight) {
        for (int i = 0; i < size; i++)
        {

           
            // Type 1 ghost mushroom
            if (arr_Mush[i] == 1)
            { 
                cout << endl;
                cout << "************************MUSH1*************************" << endl;
                cout << endl;

                // Find maxi and mini
                int maxi = 0, mini = 0;
                for (int i = 1; i < arr_NumSize; i++)
                {
                    if (arr_Num[i] >= arr_Num[maxi])
                        maxi = i;
                    if (arr_Num[i] <= arr_Num[mini])
                        mini = i;
                }
                cout << "MAXI = " << maxi <<  endl;
                cout << "MINI = " << mini << endl;
                cout << endl;

                // Calculate new HP after eating shroom
                knight.HP= knight.HP -(mini + maxi);

                // Try to Revive if HP < 0
                knight.print();
                knight.try_Revive();

                // Stop the loop if the knight can't revive 
                if (knight.HP <= 0)
                    break;
            }

            else if (arr_Mush[i] == 2)
            { 
                cout << endl;
                cout << "************************MUSH2*************************" << endl;
                cout << endl;

                if (arr_NumSize >= 1)
                { 
                    // Find the initial peak
                    find_PosPeak(pos_peak);
                    cout << "Peak of the array: " << pos_peak << endl;
                    
                    // Find new mtx and mti
                    if (check_Increment() && check_Decrement())
                    {
                        // Asign new values
                        mtx = arr_Num[pos_peak];
                        mti = pos_peak;

                        cout << "New value chosen!" << endl;
                        cout << "MTX = " << mtx << "\tMTI = " << mti << endl;
                    }

                    // Calculate new HP after eating shroom
                    knight.HP = knight.HP - (mtx + mti);

                    // Try to Revive if HP < 0
                    knight.print();
                    knight.try_Revive();

                    // Stop the loop if the knight can't revive 
                    if (knight.HP <= 0)
                        break;
                }
                

            }
            else if(arr_Mush[i] == 3)
            {
                cout << endl;
                cout << "************************MUSH3*************************" << endl;
                cout << endl;
                transformation();
                findMaxMini();

                // Calculate new HP after eating shroom
                knight.HP = knight.HP - (mini2 + maxi2);

                // Try to Revive if HP < 0
                knight.try_Revive();
                knight.print();
                // Stop the loop if the knight can't revive 
                if (knight.HP <= 0)
                    break;

            }
            else if (arr_Mush[i] == 4)
            {
                cout << endl;
                cout << "************************MUSH4*************************" << endl;
                cout << endl;
                cout << "ARR NUM SIZE: " << arr_NumSize << endl;
                transformation();
                find_2ndLargerst();

                cout << "Max X3 = " << max_x3 << "\tMax i3 = " << max_i3 << endl;


                // Calculate new HP after eating shroom
                knight.HP = knight.HP - (max_i3 + max_x3);
                knight.setHealth_toMax();
                // Try to Revive if HP < 0
                knight.try_Revive();
                knight.print();

                // Stop the loop if the knight can't revive 
                if (knight.HP <= 0)
                    break;
            }


        }
    }


};
class Pickup_Item
{
private:
public:
    Pickup_Item(Charac& knight, int code) 
    {



        if (code == 15)

            knight.remedy++;

        if (code == 16)
            knight.maidenkiss++;
        if (code == 17)
            knight.phoenixdown++;
           
        knight.set_ItemLimit();
        // In tiny form

        if (knight.form == 2)
        {
            cout << "You use the remedy you picked up!" << endl;
            knight.remedy--;
            
            // Un-tiny
            knight.HP = knight.HP * 5;
            knight.setHealth_toMax();
            
            // Reset
            knight.form = 0;
            knight.forn_count = 0;
        }


        // From frog form
        if (knight.form == 1)
        {
            cout << "You use the maidenkiss you picked up!" << endl;
            knight.maidenkiss--;

            // Un-frog
            knight.level = knight.og_LVL;

            // Reset
            knight.form = 0;
            knight.forn_count = 0;
        }

    }
};
class Merlin
{
private:
    fstream istr;
    string f_name;
    string line;

    // Check letter
    string letters1 = "merlin";
    string letters2 = "MERLIN";
    string letters3 = "Merlin";
    int n9;
    int bonus_HP = 0;
public: 
    Merlin(Charac& knight, string& prefix):f_name(prefix) {


        if (knight.merlin_Count == 0)
        {
            // Meeting for the first time
            knight.merlin_Count++;

            // Get the file's full name

            // Read the 
            istr.open(f_name);
            if (istr.is_open())
            {
                cout << "File " << f_name << " opened succesfully!!!" << endl;



                // Get n9
                getline(istr, line);
                cout << line << endl;
                n9 = stoi(line);

                // Read each line after n9
                for (int i = 0; i < n9; i++)
                {
                    getline(istr, line);
                    if (checkEnchanted2(line))
                    { 
                        cout << "HP+3" << endl;
                        bonus_HP = 3;
                    }
                    else if (checkEnchanted(line))
                    { 
                        cout << "HP+2" << endl;
                        bonus_HP = 2;
                    }
                    knight.HP += bonus_HP;
                    knight.setHealth_toMax();
                }
        }

        }

    }

private:
    bool checkEnchanted(string& line)
    {

        if (line.size() < 6)
            return false;

        int count = 0;
        for (int i = 0; i < line.size(); i++)
        {


            for (int j = 0; j < 6; j++)
            {
                if (line.at(i) == letters1.at(j) || line.at(i) == letters2.at(j))
                {
                    count++;
                    break;
                }
            }
        }


        return (count >= 6);
    }
    bool checkEnchanted2(string& line) {
        if (line.size() < 6)
            return false;


        for (int i = 0; i < line.size() - 5; i++)
        {
            if (line.at(i) == letters1.at(0) || line.at(i) == letters3.at(0))
            {
                if (line.substr(i, 6) == letters1 || line.substr(i, 6) == letters3)
                    return true;
            }
        }

        return false;
    }
};
class God {
private:
    fstream istr;
    string f_name;
    string line = "0";
    

    // Array
    int* arr_Potion;

    int r1;
    int c1;
    int count_Potion = 0;
public:

    // Check letter

    God(Charac& knight, const string& fname):f_name(fname) {
        if (knight.god_Count == 0)
        {
            knight.god_Count++;

            // Read the 
            istr.open(f_name);
            cout << "God file name: " <<f_name << endl;

            if (istr.is_open())
            {
                cout << "File " << f_name << " opened succesfully!!!" << endl;

                // Get r1
                getline(istr, line);
                cout << "R1 = " << line << endl;
                r1 = stoi(line);
                
                // Get c1
                getline(istr, line);
                    c1 = stoi(line);
                    cout << "C1 = " << line << endl;


                    arr_Potion = new int[c1];
                // Read each line after c1
                for (int i = 0; i < r1; i++)
                {
                    getline(istr, line);
                    tokenizer(line);
                    count_Potion = 0;
                    // Gather the pack of potion
                    for (int j = 0; j < c1; j++)
                    {
                        if (count_Potion ==3)
                            break;

                        collect(arr_Potion[j], knight,  count_Potion);
                    }
                }


                delete[] arr_Potion;
            }
        }
    }

private:
    void tokenizer(string& line) {

        string::size_type wEnd, wStart;
        string delimeter = " ";
        wStart = line.find_first_not_of(delimeter, 0);

        for (int i = 0; i < c1; i++)
        {
            wEnd = line.find_first_of(delimeter, wStart);
            arr_Potion[i] = stoi(line.substr(wStart, wEnd - wStart));
            wStart = line.find_first_not_of(delimeter, wEnd);

            // Print

            cout << arr_Potion[i] << "\t";

        }
        cout << endl;
    }
    void collect(int code, Charac& knight, int& count_Potion) {
        if (code == 16 || code == -16)
        { 
            knight.remedy++;
            count_Potion++;
        }
        if (code == 17 || code == 17)
        {
            knight.maidenkiss++;
            count_Potion++;
        }
        if (code == 18 || code == 18)
        {
            knight.phoenixdown++;
            count_Potion++;
        }
        knight.set_ItemLimit();
        // In tiny form

        if (knight.form == 2)
        {
            cout << "You use the remedy you picked up!" << endl;
            knight.remedy--;

            // Un-tiny
            knight.HP = knight.HP * 5;
            knight.setHealth_toMax();

            // Reset
            knight.form = 0;
            knight.forn_count = 0;
        }


        // From frog form
        if (knight.form == 1)
        {
            cout << "You use the maidenkiss you picked up!" << endl;
            knight.maidenkiss--;

            // Un-frog
            knight.level = knight.og_LVL;

            // Reset
            knight.form = 0;
            knight.forn_count = 0;
        }


    }
};
void package_Token(string&, string&, string&, string& package);
void go_Adventure(int* arr, int size, Charac& knight, const string& prefix,string& ghost, string& god, string& merlin);
void debuff_Tracker(Charac& knight);

#endif // __KNIGHT_H__