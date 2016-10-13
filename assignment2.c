/*
    A program that simulates the National Lottery.
    The game provides a menu for the user to interact with.
    
    Functions are used to modularise each menu item.
    
    An array of static ints is used to remember the frequency of each number entered until the program is exited.
    
    Compiled with Borland Compiler

    Ronan Connolly DT228
    C15737505
    
    02/03/2016
*/

#include <stdio.h>
#include <ctype.h>

#define SIZE 6
#define FREQ_SIZE 43

//prototypes
void menu();
int get_user_numbers(int*);
void display_user_numbers(int*);
void sort_algorithm(int*);
void check_numbers(int*, int*);
void display_frequency(int*, int*);


main()
{
    //run game
    menu();
    
    getchar();
    getchar();
    
    
}//end main()

//function implementation
//f_ means function variable
void menu()
{
    //for menu loop
    bool menu_running = true;
    
    //used for user's menu choice
    int user_menu_input = 0;
    int duplicate_check = -1;
    int menu_error;
    
    //array to store user's numbers in. 
    //winning_num array has bonus number[SIZE + 1]   ----42-----
    int user_num_array[SIZE];
    int winning_num[SIZE + 1] = {1,3,5,7,9,11,42}; 
    
    //keeps count of frequency of each number the user picks, intialize to zero
    static int frequency_array[FREQ_SIZE] = {0};
    
    //MENU
    while(menu_running)
    {
        //display menu
        printf("\t\t\t***********************************\n");
        printf("\t\t\t*\t Welcome to Lotto         *\n");
        printf("\t\t\t***********************************\n");
        printf("\n");
        printf("1. Enter your numbers: \n");
        printf("2. Display your numbers: \n");
        printf("3. Sort your numbers(low to high):\n");
        printf("4. Check your numbers:\n");
        printf("5. Display number frequency: \n");
        printf("6. Exit: \n\n");
        
        //Prompt user and get user menu choice
        //Using scanf return type to check for non numeric entry
        printf("\nPlease choose from the menu(1-6)\n");
        printf("---------------------------------------\n");
        
        menu_error = scanf("%d", &user_menu_input);
        
        //error check user menu choice
        if(user_menu_input <= 0 || user_menu_input > 6 || menu_error == 0)
        {
            //wrong input stays in buffer and causes infinite loop. This gets rid of the offending character.
            fflush(stdin);
        }
        
        //process user choice
        switch(user_menu_input)
        {
            case 1:
                //this function will return 1 if there IS duplicates and will run until there is not(0)
                //If the duplciate_check = 1 it means inccorect input or menu number 1 has not been run yet.
                //The other menu options wont work until correct input
                do
                {                    
                    duplicate_check = get_user_numbers(user_num_array);
                }while(duplicate_check != 0);
                    
                break;
            case 2:
                
                if(duplicate_check != 0)
                {
                    printf("You must select 1 first!\n");
                    break;
                }//End if
                
                //display
                display_user_numbers(user_num_array);
                break;
            case 3:
                
                if(duplicate_check != 0)
                {
                    printf("You must select 1 first!\n");
                    break;
                }//End if
                
                //sort
                sort_algorithm(user_num_array);
                break;
            case 4:
                
                if(duplicate_check != 0)
                {
                    printf("You must select 1 first!\n");
                    break;
                }//End if
                
                //check numbers
                check_numbers(user_num_array,winning_num);
                break;
            case 5:
                
                if(duplicate_check != 0)
                {
                    printf("You must select 1 first!\n");
                    break;
                }//End if
                
                //frequency
                display_frequency(frequency_array,user_num_array);
                break;
            case 6:
                //Exit program
                printf("\nThanks for playing!! Goodbye\n");
                menu_running = false;
                break;
            default:
                printf("\n!!!Error: invalid Input: Please choose from (1 - 6)\n\n");
                break;
                    
            
        }//end switch
        
    }//end while
}//end menu()

int get_user_numbers(int *f_user_num_array)
{
    int user_num_error = 0;
    
    
    printf("Please enter numbers(%d MAX)\n\n", SIZE);
    for(int i = 0; i < SIZE; i++)
    {
        user_num_error = scanf("%d", f_user_num_array + i);
        
        //error check for correct number range and check for characters entered with scanf return type
        if(*(f_user_num_array + i) <= 0 || *(f_user_num_array + i) > 42 || user_num_error == 0)
        {
            printf("Please choose betwen 1 and 42( No characters )\n");
            printf("-------------------------------------------------\n\n");
            
            fflush(stdin);
            //return type is used to check for wrong input
            return 1;
        }
        
        //check for duplicates. 
        for(int j = 0; j < i; j++)
        {
            if(*(f_user_num_array + i) == *(f_user_num_array + j))
            {
                printf("Duplicate!:\n");
                return 1;
            }//end if
            
        }//end for
            
    }//end for
    
    //input is fine
    return 0;
    
}//end get_user_numbers()

void display_user_numbers(int *f_user_num_array)
{
    printf("\nYour numbers are:\n");
    for(int i = 0; i < SIZE; i++)
    {
        printf("%d ", *(f_user_num_array + i));
    }//end for
    
    //without this newline the top of the menu gets cut off
    printf("\n");
}//end display_user_number()

void sort_algorithm(int *f_user_num_array)
{
    //SELECTION SORT
    for(int i = 0; i < SIZE; i++)
	{
		int index_of_min = i;

		for(int j = i; j < SIZE; j++)
		{
			if(*(f_user_num_array + index_of_min) > *(f_user_num_array + j))
			{
				index_of_min = j;
			}//end if
		}//end for

		int temp = *(f_user_num_array + i);
		*(f_user_num_array + i) = *(f_user_num_array + index_of_min);
		*(f_user_num_array + index_of_min) = temp;

	}
}//end sort_algorithm()

void check_numbers(int *f_user_num_array,int *f_win_num)
{
    //stores the each element of the users array so it can be check against the entire winning number array
    int user_temp_num = 0;
    //used to increment user array after the number has been checked  against the entire winning number array
    int array_index = 0;
    //keeps track of match
    int match_count = 0;
    //if bonus_match is true the user has matched the bonus and the dispaly switch case will output appropriately
    bool bonus_match = false;
    
    //set the bonus number to the last element of the winning numbers array
    int bonus_num = *(f_win_num + SIZE);
    
    //check each number in user array against every number in winning array
    while(array_index < SIZE)
    {
        //user_temp_num is set to EACH element in f_user_num_array after the loop is complete
        user_temp_num = *(f_user_num_array + array_index);
        
        //check one number against all the numbers in the winning array
        for(int i = 0; i < SIZE; i++)
        {
            //check if match 
           if(user_temp_num == *(f_win_num + i))
           {
               match_count++;
           }//end if
           
            //check for bonus number *(f_win_num + (SIZE + 1))
           if(user_temp_num == bonus_num)
           {
                bonus_match = true;
           }//end if
           
        }//end for
        
        //increment the index so next time around the loop it will check the next number
        array_index++;
        
    }//end while    
    
    //print winning numbers 
    //and bonus number
    printf("WINNING NUMBERS: \n");
    for(int i = 0; i < SIZE; i++)
    {
        printf("%d ", *(f_win_num + i));
    }
    
    //printf Bonus number at end with some ** to differentiate it from the other numbers
    printf("\t**BONUS NUMBER: %d**\n\n", bonus_num);
    
    
    //DISPLAY RESULT
    switch(match_count)
    {
             case 1:
                printf("No prize won. Please play again.\n");
                break;
             
            case 2:
                printf("No prize won. Please play again.\n");
                break;
            
            case 3:
                
                if(bonus_match == true)
                {
                    printf("------------------\n");
                    printf("Match 3 + Bonus: Cinema ticket\n");
                    printf("------------------\n");
                }//end if
                else
                {
                    printf("No prize won. Please play again.\n");
                }
                
                break;
            case 4:
                
                if(bonus_match == true)
                {
                    printf("------------------\n");
                    printf("Match 4 + Bonus: Weekend away\n");
                    printf("------------------\n");
                }
                else
                {
                    printf("------------------\n");
                    printf("Match 4: Night out\n");
                    printf("------------------\n");
                }//end else
                
                break;
            case 5:
                
            if(bonus_match == true)
                {
                    printf("------------------\n");
                    printf("Match 5 + Bonus: New car\n");
                    printf("------------------\n");
                }
                else
                {
                    printf("------------------\n");
                    printf("Match 5: Holiday\n");
                    printf("------------------\n");
                }//end else
                
                break;
            case 6:
                
                printf("------------------\n");
                printf("Match 6: JACKPOT!!!\n");
                printf("------------------\n");
            
                break;
            default:
                printf("No prize won. Please play again.\n");
                break;
    }//end switch
    
}//end check_numbers()

void display_frequency(int *static_array, int *f_user_num_array)
{
    //loop through user array
    for(int i = 0; i < SIZE; i++)
    {
        //store each value of user array in temp to be used as the index for static array
        int temp_index = *(f_user_num_array + i);
       
        *(static_array + temp_index) = *(static_array + temp_index) + 1;
        
    }
    //if user number is equal to static array index, increament at that index.
    
    //printf Frequency
    printf("\n");
    for(int i = 1; i < FREQ_SIZE;i++)
    {
        //printf a blank line if the index hasnt been incremented
        if(*(static_array + i) == 0)
        {
            printf("");
        }
        else
        {
            //NOTE TO SELF: double check index here. it will be one off????
            printf("Number %d has been selected %d times.\n",i, *(static_array + i));
        }//end else
    }//end for
    
    
}//end display_frequency()