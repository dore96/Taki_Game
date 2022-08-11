/*Name: Dor Edelman.
* program name: taki_project.c*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>	
#include <stdbool.h>
#include <string.h>

#define MAX_NAME_LEN 21                                     //maximum name length
#define MAX_SPECIAL_LEN 30									//cards name length
#define NUM_OF_CARDS_START 4								//starting number of cards per player
#define NUM_OF_CARDS_TYPE 14								//number of types of cards
#define CARD_WIDTH  9										//card phisical length (print)
#define CARD_LENGTH 6										//card phisical width (print)
#define NONE 0												//int of none 
#define ONE 1												//int of one
#define HALF 2											    //represents number 2.
#define ONE_IND 1											//represents one index
#define ONE_ID 1											//represents card type '1'
#define TWO_ID 2											//represents card type '2'
#define THREE_ID 3											//represents card type '3'
#define FOUR_ID 4											//represents card type '4'
#define FIVE_ID 5											//represents card type '5'
#define SIX_ID 6											//represents card type '6'
#define SEVEN_ID 7											//represents card type '7'
#define EIGHT_ID 8											//represents card type '8'
#define NINE_ID 9											//represents card type '9'
#define PLUS_ID 10											//represents card type 'plus'
#define CAHNGE_DIRACTION_ID 11								//represents card type 'change diraction'
#define TAKI_ID 12											//represents card type 'taki'
#define STOP_ID 13											//represents card type 'stop'
#define COLOR_ID 14											//represents card type 'color'

typedef struct card                                         //struct of cards 
{
	int card_id;											//represents in integer the type of card (esier to compare)
	char color;												//color of the card
	char card[MAX_SPECIAL_LEN];								//type of card
} card;

typedef struct player										//struct of player
{
	int num_of_cards;										//number of logical size of cards in hand
	int number_of_space_cards;								//number of pyisical size of cards in hand
	char player_name[MAX_NAME_LEN];							//players name string
	card* player_cards;										//a dinamic array of card type.
} player_data;

typedef struct statistic_count								//counter of statistic
{
	char card[MAX_SPECIAL_LEN];								//type of card
	int counter;											//number of appirence in game counter
}statistic_count;

int greet_and_num_of_players();                                                                                     //function perpuse is to greet user and returns number of players.
void get_players_names(player_data* players, int number_of_players);												//function perpuse is to get players names.
void deal_cards(player_data* players, int number_of_players, card* upper_card, statistic_count statistic[]);		//function perpuse is to deal the starting cards.
void pick_card_value(card* players_card, int random, statistic_count statistic[]);									//function perpuse is to pick a card type.
void pick_card_color(card* players_card, int random);																//function perpuse is to pick a card color.
void print_card(card* card);																						//function perpuse is to print card.
bool players_turn(player_data* player, card* upper_card, int* diraction, int* player_index, statistic_count statistic[]);//function perpuse is to play players whole turn , returns if there is a winner.
int make_user_choice_valid(player_data* player, card* upper_card, int user_choice);									//function perpuse is to deals with user choice validation returns valid one.
bool check_user_choice(card players_card, card upper_card);														    //function perpuse is to return if user choice of card is valid.
void erase_card(player_data* player, card* upper_card, int user_choice);											//function perpuse is to update upper card and erase from players hand.
void pick_card(player_data* player, statistic_count statistic[]);													//function perpuse is to pick a card.
void special_card(player_data* player, card* upper_card, int user_choice);											//function perpuse is to deal with special cards
void print_upper_and_player_card(player_data* player, card* upper_card);											//function perpuse is to print upper and players cards.
void taki_card(player_data* player, card* upper_card);																//function perpuse is to deal with taki card rules.
bool check_after_taki(card players_card, card upper_card);															//function perpuse is to check if card is valid (after taki) returns t\f.
bool last_taki_card(player_data* player, card* upper_card, int* diraction, int* player_index, bool finished_cards, statistic_count statistic[]);  //function perpuse is to check the last card after taki.
card* make_more_card_space(player_data* player);																	//function perpuse is to make more space in dinamic arrays (realloc). returns cards new pointer.
int correct_index(int index, int diraction, int number_of_players);													//function perpuse is to make index valid.
void print_winner_and_statistics(statistic_count statistic[], player_data* players, int player_ind);				//function perpuse is to print the game stats.
void initiate_dinamic(int player_ind, int number_of_players, player_data players[]);								//function perpuse is to initiate dinamic arrays.
void reset_counter(statistic_count statistic[]);																	//function perpuse is to reset statistic counter.
void counter_type(int index, statistic_count statistic[]);															//function perpuse is to insert statistic card types;
void copyArr(statistic_count dest[], statistic_count src[], int size);												//function perpuse is to copy array.
statistic_count* merge(statistic_count a1[], int size1, statistic_count a2[], int size2);							//function perpuse is to merge two arrays into one , returns a pointer to new array.
void merge_sort(statistic_count statistic[], int size);																//function perpuse is to sort an array recursively with dinamic arrays.
void color_card(player_data* player, int user_choice);																//function perpuse is to handel color card
bool plus_card(player_data* player, card* upper_card, statistic_count statistic[], int user_choice, bool finished_cards, int* diraction, int* player_index);//function perpuse is to handel plus card.
void free_dinamics(int player_ind, int number_of_players, player_data players[]);									//function perpuse is to free all dinamic arrays.

void main()
{
	int number_of_players, player_ind = NONE, diraction = ONE;                                      //number of players , player index , direction of the game.
	player_data* players = NULL;																	//dinamic array of players struct.
	statistic_count statistic[NUM_OF_CARDS_TYPE];													//array for each card type for statistic
	bool there_is_winner = false;																	//bolien there is a winner
	card upper_card;																				//upper card struct
	srand(time(NULL));			

	number_of_players = greet_and_num_of_players();													//greet welcom and get number of player .
	players = (player_data*)malloc(number_of_players * sizeof(player_data));						//dinamic array the initiate by number of players.
	if (!players)																					//if fail, exit.
		exit(1);
	initiate_dinamic(player_ind, number_of_players, players);										//initiate dinamic arrays for each player cards
	get_players_names(players, number_of_players);													
	deal_cards(players, number_of_players, &upper_card, statistic);                                 //generate starting cards.
	while (!there_is_winner)																		//while there isnt a winner
	{
		there_is_winner = players_turn(&players[player_ind], &upper_card, &diraction, &player_ind, statistic);	//play players turn ,returns is there is a winner
		if (!there_is_winner)																					//if there isnt correct index.
			player_ind = correct_index(player_ind, diraction, number_of_players);
	}
	print_winner_and_statistics(statistic, players, player_ind);									//print how is the winner and statistics.
	free_dinamics(player_ind, number_of_players, players);											//free all dinamic arrays.
}

bool players_turn(player_data* player, card* upper_card, int* diraction, int* player_index, statistic_count statistic[]) //function perpuse is to play players whole turn , returns if there is a winner.O(players->number_of_cards)
{
	int user_choice;
	bool finished_cards = false;

	print_upper_and_player_card(player, upper_card);                            //prints the upper card and players cards

	printf("Please enter 0 if you want to take a card from the deck\n"
		"or 1 - %d if you want to put one of your cards in the middle : \n", player->num_of_cards);
	scanf("%d", &user_choice);

	user_choice = make_user_choice_valid(player, upper_card, user_choice);      //makes sure the users input is correct

	switch (player->player_cards[user_choice - ONE_IND].card_id)                //switch to speciel card cases
	{
	case COLOR_ID:																//in case of color card.
		color_card(player, user_choice);
		break;
	case PLUS_ID:																//in case of plus card.
		finished_cards = plus_card(player, upper_card, statistic, user_choice, finished_cards, diraction, player_index);
		return finished_cards;
		break;
	case TAKI_ID:                                                               //in case of taki , replace , erase card to upper and then check.
		erase_card(player, upper_card, user_choice);
		taki_card(player, upper_card);
		finished_cards = last_taki_card(player, upper_card, diraction, player_index, finished_cards, statistic);  //finish the turn after knowing if left more cards or winner found.
		return finished_cards;
		break;
	case STOP_ID:																//in case of stop card, add index of player.
		*player_index += *diraction;
		break;
	case CAHNGE_DIRACTION_ID:													//in case of change direction card, change direction to negative\positive.
		*diraction = *diraction * (-ONE);
		break;
	}

	if (user_choice == NONE)														//if user want to take a card, else replace in upper and erase the user choise
		pick_card(player, statistic);
	else
		erase_card(player, upper_card, user_choice);

	if (player->num_of_cards == NONE)                                             //if no cards left to player, finished cards positive.
		finished_cards = !finished_cards;
	return finished_cards;
}

int greet_and_num_of_players() //function perpuse is to greet user and returns number of players.O(1)
{
	int number_of_players;
	printf("************  Welcome to TAKE game !!! ************\n"
		"Please enter number of players:\n");
	scanf("%d", &number_of_players);
	return number_of_players;
}

void get_players_names(player_data* players, int number_of_players) //function perpuse is to get players names. O(number_of_players)
{
	int i;
	for (i = ONE; i <= number_of_players; i++)
	{
		printf("Please enter the first name of player #%d:\n", i);
		scanf("%s", players[i - ONE_IND].player_name);
	}
}

void deal_cards(player_data* players, int number_of_players, card* upper_card, statistic_count statistic[]) //function perpuse is to deal the starting cards.O(number_of_players)
{
	int player_ind, card_ind;
	reset_counter(statistic);													 //reset counter statistic.
	for (player_ind = NONE; player_ind < number_of_players; player_ind++)        //for each player
	{
		players[player_ind].num_of_cards = NONE;								  //initiate num of cards per player (logical number)
		for (card_ind = NONE; card_ind < NUM_OF_CARDS_START; card_ind++)         //4 iterations for each player to get cards
			pick_card(&players[player_ind], statistic);                       //pick randome card for current player card
		players[player_ind].number_of_space_cards = NUM_OF_CARDS_START;
	}
	pick_card_value(upper_card, (rand() % NUM_OF_CARDS_TYPE) + ONE, statistic);				  //pick randome card for upper card
	while (strcmp(upper_card->card, "COLOR") == NONE)                            //if upper card start is color change it (game rules)
		pick_card_value(upper_card, (rand() % NUM_OF_CARDS_TYPE) + ONE, statistic);

}

void pick_card_value(card* players_card, int num, statistic_count statistic[])  //function perpuse is to pick a card type.O(1)
{
	switch (num)                                        //pick a card to the number entered, update card and card id
	{
	case ONE_ID:    strcpy(players_card->card, "1");
		players_card->card_id = ONE_ID;
		break;
	case TWO_ID:	strcpy(players_card->card, "2");
		players_card->card_id = TWO_ID;
		break;
	case THREE_ID:	strcpy(players_card->card, "3");
		players_card->card_id = THREE_ID;
		break;
	case FOUR_ID:	strcpy(players_card->card, "4");
		players_card->card_id = FOUR_ID;
		break;
	case FIVE_ID:	strcpy(players_card->card, "5");
		players_card->card_id = FIVE_ID;
		break;
	case SIX_ID:	strcpy(players_card->card, "6");
		players_card->card_id = SIX_ID;
		break;
	case SEVEN_ID:	strcpy(players_card->card, "7");
		players_card->card_id = SEVEN_ID;
		break;
	case EIGHT_ID:	strcpy(players_card->card, "8");
		players_card->card_id = EIGHT_ID;
		break;
	case NINE_ID:	strcpy(players_card->card, "9");
		players_card->card_id = NINE_ID;
		break;
	case TAKI_ID:	strcpy(players_card->card, "TAKI");
		players_card->card_id = TAKI_ID;
		break;
	case CAHNGE_DIRACTION_ID:	strcpy(players_card->card, "<->");
		players_card->card_id = CAHNGE_DIRACTION_ID;
		break;
	case PLUS_ID:	strcpy(players_card->card, "+");
		players_card->card_id = PLUS_ID;
		break;
	case STOP_ID:    strcpy(players_card->card, "STOP");
		players_card->card_id = STOP_ID;
		break;
	case COLOR_ID: 	 strcpy(players_card->card, "COLOR");
		players_card->card_id = COLOR_ID;
		players_card->color = ' ';
		break;
	}
	statistic[num - ONE_IND].counter++;                                //update ststistics counter
	if (num != COLOR_ID)										      //if card isnt a color card pick a color
		pick_card_color(players_card, rand() % FOUR_ID);
}

void pick_card_color(card* players_card, int num) //function perpuse is to pick a card color.O(1)
{
	switch (num)                                  //pick a color to card by random number in func.
	{
	case NONE: players_card->color = 'Y';
		break;
	case ONE_ID: players_card->color = 'R';
		break;
	case TWO_ID: players_card->color = 'B';
		break;
	case THREE_ID: players_card->color = 'G';
		break;
	}
}

void print_card(card* card)            //function perpuse is to print card.O(1)(9*6 for loop)
{
	int row, col;

	for (row = NONE; row < CARD_LENGTH; row++)                   //for every row
	{
		for (col = NONE; col < CARD_WIDTH; col++)				  //for every colom
		{
			if (card->card_id < CAHNGE_DIRACTION_ID) {               //if card is a number or plus
				if ((row == HALF) && (col == FOUR_ID))                 //if in right location of card, print card 
				{
					printf("%s", card->card);
					col++;
				}
			}
			else                                             //if card is speciel len (>1)
			{
				if (card->card_id == NUM_OF_CARDS_TYPE) {					 //if color(5 len)
					if ((row == HALF) && (col == HALF))			 //if in right location of card, print card
					{
						printf("%s", card->card);
						col += strlen(card->card);
					}
				}
				else if ((row == HALF) && (col == THREE_ID))           //if speciel but not color print card in place
				{
					printf("%s", card->card);
					col += strlen(card->card);
				}
			}
			if ((row == THREE_ID) && (col == FOUR_ID) && card->color != ' ')
			{
				printf("%c", card->color);
				col++;
			}
			if ((row == NONE) || (row == CARD_LENGTH - ONE) || (col == NONE) || (col == CARD_WIDTH - ONE))    //if is edge print * else print space.
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}

int make_user_choice_valid(player_data* player, card* upper_card, int user_choice) //function perpuse is to deals with user choice validation returns valid one.O(1)
{
	//while user choice is bigger then num of cards or wrong card wise get another input.
	while (!check_user_choice(player->player_cards[user_choice - ONE_IND], *upper_card) && user_choice != NONE || player->num_of_cards < user_choice)
	{
		printf("Invalid choice! Try again.\n"
			"Please enter 0 if you want to take a card from the deck\n"
			"or 1 - %d if you want to put one of your cards in the middle : \n", player->num_of_cards);
		scanf("%d", &user_choice);
	}
	return user_choice;
}

bool check_user_choice(card players_card, card upper_card) //function perpuse is to return if user choice of card is valid.O(1)
{
	bool is_valid = false;
	if (upper_card.card_id > PLUS_ID) {																  //upper card is not a number
		if (players_card.color == upper_card.color || upper_card.card_id == players_card.card_id || players_card.card_id == COLOR_ID) //color or number is a match
			is_valid = !is_valid;
	}
	else {																							   //upper card is a number
		if (players_card.card_id < CAHNGE_DIRACTION_ID) {                                                                //users card is a number
			if (players_card.color == upper_card.color || upper_card.card_id == players_card.card_id)  //number is bigger and same color
				is_valid = !is_valid;
		}
		else																					      //users card is not a number
		{
			if (players_card.color == upper_card.color || upper_card.card_id == players_card.card_id || players_card.card_id == COLOR_ID)//color or number is a match or a color card
				is_valid = !is_valid;
		}
	}
	return is_valid;
}

void erase_card(player_data* player, card* upper_card, int user_choice) //function perpuse is to update upper card and erase from players hand.O(1)
{
	*upper_card = player->player_cards[user_choice - ONE_IND];                                    //swap upper card to player card
	player->player_cards[user_choice - ONE_IND] = player->player_cards[player->num_of_cards - ONE_IND];	//place last card in the used card place
	player->num_of_cards--;
}

void pick_card(player_data* player, statistic_count statistic[]) //function perpuse is to pick a card.O(1)
{
	if (player->number_of_space_cards == player->num_of_cards)
		player->player_cards = make_more_card_space(player);
	pick_card_value(&player->player_cards[player->num_of_cards], (rand() % NUM_OF_CARDS_TYPE) + ONE, statistic);
	player->num_of_cards++;
}

void print_upper_and_player_card(player_data* player, card* upper_card) //function perpuse is to print upper and players cards.O(player->number_of_cards)
{
	int current_card;
	for (current_card = NONE; current_card < player->num_of_cards; current_card++)  //for every card in players hand
	{
		if (current_card == NONE)													 //upper card print
		{
			printf("\nUpper card\n");
			print_card(upper_card);
			printf("\n%s's turn:\n", player->player_name);
		}
		printf("Card #%d:\n", current_card + ONE_IND);							//players card print
		print_card(&player->player_cards[current_card]);
	}
}

void taki_card(player_data* player, card* upper_card) //function perpuse is to deal with taki card rules.O(number_of_user_choice)
{
	int user_choice = ONE;																				
	print_upper_and_player_card(player, upper_card);													
	while (user_choice != NONE)																				//while user want to continue
	{
		printf("Please enter 0 if you want to finish your turn\n"											//print message and ger user choice of action.
			"or 1 - %d if you want to put one of your cards in the middle :\n", player->num_of_cards);
		scanf("%d", &user_choice);
		if (user_choice <= player->num_of_cards && user_choice != NONE)										//if user choise is in range of cards and not 0
		{
			if (check_after_taki(player->player_cards[user_choice - ONE_IND], *upper_card))					//check if card is valid to put
			{
				erase_card(player, upper_card, user_choice);												//if card is valid , update upper and erase from deck
				if (upper_card->card_id == COLOR_ID)														//if card is color , stop taki
					return;
				else
					print_upper_and_player_card(player, upper_card);										//if not color , print cards
			}
			else
				printf("Invalid card! Try again.");															//if card isnt valid to put print error
		}
		else if (user_choice != NONE)																		//if user choise is in not in range of cards and not 0
			printf("Invalid card! Try again.");
	}
}

bool check_after_taki(card players_card, card upper_card) //function perpuse is to check if card is valid (after taki) returns t\f.O(1)
{
	bool is_valid = false;
	if (players_card.color == upper_card.color || players_card.card_id == COLOR_ID)             //if colors are the same of players card is color make valid
		is_valid = !is_valid;
	return is_valid;
}

bool last_taki_card(player_data* player, card* upper_card, int* diraction, int* player_index, bool finished_cards, statistic_count statistic[]) //function perpuse is to check the last card after taki.O(1)
{
	int color_choice;
	switch (upper_card->card_id)                //switch to speciel card cases
	{
	case COLOR_ID:																//in case of color card.
		printf("Please enter your color choice:\n1 - Yellow\n2 - Red\n"
			"3 - Blue\n4 - Green\n");
		scanf("%d", &color_choice);
		pick_card_color(upper_card, color_choice - ONE_IND);
		break;
	case PLUS_ID:																//in case of plus card.
		if (player->number_of_space_cards == player->num_of_cards)
			player->player_cards = make_more_card_space(player);
		pick_card(player, statistic);
		break;
	case STOP_ID:																//in case of stop card, add index of player.
		*player_index += *diraction;
		break;
	case CAHNGE_DIRACTION_ID:													//in case of change direction card, change direction to negative\positive.
		*diraction = *diraction * (-ONE);
		break;
	}
	if (player->num_of_cards == NONE)
		finished_cards = !finished_cards;
	return finished_cards;
}

card* make_more_card_space(player_data* player) //function perpuse is to make more space in dinamic arrays (realloc). returns cards new pointer.O(player->num_of_cards)
{
	card* tmp = NULL;
	int i;

	player->number_of_space_cards *= TWO_ID;								//multiply space in array by 2
	tmp = (card*)malloc(player->number_of_space_cards * sizeof(card));
	if (!tmp)                                                               //if malloc faild exit(1)
		exit(ONE);
	for (i = NONE; i < player->num_of_cards; i++)                              //take all to temp array 
		tmp[i] = player->player_cards[i];

	free(player->player_cards);												//free previews location of array
	player->player_cards = tmp;												//point at new bigger array
	return player->player_cards;
}

int correct_index(int index, int diraction, int number_of_players) //function perpuse is to make index valid.O(1)
{
	index += diraction;                                             //menipulation on index to fit the right place of player.
	if (index >= number_of_players)
		index = index - number_of_players;
	if (index < NONE)
		index = number_of_players + index;
	return index;
}

void print_winner_and_statistics(statistic_count statistic[], player_data* players, int player_ind) //function perpuse is to print the game stats.O(1)
{
	int index;
	printf("the winner is...  %s! , congratulation!\n\n", players[player_ind].player_name);
	printf("************ Game Statistic ************\n"
		"card # | frequency\n"
		"__________________\n");
	merge_sort(statistic, NUM_OF_CARDS_TYPE);																//merge sort statistic arr.
	for (index = NONE; index < NUM_OF_CARDS_TYPE; index++)														//for every card type there is (14)
	{
		switch (strlen(statistic[index].card))																//check card len to print correctly sorted statistics
		{
		case ONE_ID: printf("   %-4s| %4d\n", statistic[index].card, statistic[index].counter);
			break;
		case THREE_ID:  printf("  %s  | %4d\n", statistic[index].card, statistic[index].counter);
			break;
		case FOUR_ID:  printf("  %s | %4d\n", statistic[index].card, statistic[index].counter);
			break;
		case FIVE_ID:  printf(" %s | %4d\n", statistic[index].card, statistic[index].counter);
			break;
		}
	}
}

void initiate_dinamic(int player_ind, int number_of_players, player_data players[]) //function perpuse is to initiate dinamic arrays.O(number_of_players)
{
	for (player_ind = NONE; player_ind < number_of_players; player_ind++)       //initiate dinamic array of cards for every player , if fail , exit(1)
	{
		players[player_ind].player_cards = NULL;
		players[player_ind].player_cards = (card*)malloc(NUM_OF_CARDS_START * sizeof(card));
		if (!players[player_ind].player_cards)
			exit(1);
	}
}

void reset_counter(statistic_count statistic[])     //function perpuse is to reset statistic counter.O(1)
{
	int index;
	for (index = NONE; index < NUM_OF_CARDS_TYPE; index++)                        //for every card type there is initiate valuse. 
	{
		statistic[index].counter = NONE;
		counter_type((index), statistic);
	}
}

void counter_type(int index, statistic_count statistic[]) //function perpuse is to insert statistic card types;O(1)
{
	switch (index + ONE_IND)                                             //switch to insert the correct name to card.
	{			         //it seems like the same switch as pick a card but i used a tequnic of cards id to be efficient without a lot of str len\cmp.
	case ONE_ID: strcpy(statistic[index].card, "1");
		break;
	case TWO_ID:  strcpy(statistic[index].card, "2");
		break;
	case THREE_ID:  strcpy(statistic[index].card, "3");
		break;
	case FOUR_ID:  strcpy(statistic[index].card, "4");
		break;
	case FIVE_ID:  strcpy(statistic[index].card, "5");
		break;
	case SIX_ID:  strcpy(statistic[index].card, "6");
		break;
	case SEVEN_ID:  strcpy(statistic[index].card, "7");
		break;
	case EIGHT_ID:  strcpy(statistic[index].card, "8");
		break;
	case NINE_ID:  strcpy(statistic[index].card, "9");
		break;
	case PLUS_ID:  strcpy(statistic[index].card, "PLUS");
		break;
	case STOP_ID:  strcpy(statistic[index].card, "STOP");
		break;
	case CAHNGE_DIRACTION_ID:  strcpy(statistic[index].card, "<->");
		break;
	case TAKI_ID: strcpy(statistic[index].card, "TAKI");
		break;
	case COLOR_ID: strcpy(statistic[index].card, "COLOR");
		break;
	}
}

void merge_sort(statistic_count statistic[], int size) //function perpuse is to sort an array recursively with dinamic arrays.O(size*log(size))
{
	statistic_count* tmpArr = NULL;
	if (size <= ONE)
		return;

	merge_sort(statistic, size / HALF);                                                //recursive call "left side"
	merge_sort(statistic + size / HALF, size - size / HALF);                              //recursive call "right side"
	tmpArr = merge(statistic, size / HALF, statistic + size / HALF, size - size / HALF);		//temparr gets a pointer of merged statistic sorted
	if (tmpArr)
	{
		copyArr(statistic, tmpArr, size); // copy values from tmpArr to statistic
		free(tmpArr);
	}
	else
		exit(ONE);	// end program immediately with code 1 (indicating an error)
}

statistic_count* merge(statistic_count a1[], int size1, statistic_count a2[], int size2) //function perpuse is to merge two arrays into one , returns a pointer to new array.O(size1+size2)
{
	int ind1, ind2, resInd;
	statistic_count* res = (statistic_count*)malloc((size1 + size2) * sizeof(statistic_count));

	if (res)                                               //res is not null
	{
		ind1 = ind2 = resInd = NONE;

		while ((ind1 < size1) && (ind2 < size2))          //while there are more to insert res
		{
			if (a1[ind1].counter > a2[ind2].counter)      //if counter of number 1 is bigger place in res , else place there number 2.
			{
				res[resInd] = a1[ind1];
				ind1++;
			}
			else
			{
				res[resInd] = a2[ind2];
				ind2++;
			}
			resInd++;
		}
		while (ind1 < size1) {                            //if left in a1 more to insert
			res[resInd] = a1[ind1];
			ind1++;
			resInd++;
		}
		while (ind2 < size2) {                            //if left in a2 more to insert
			res[resInd] = a2[ind2];
			ind2++;
			resInd++;
		}
	}
	return res;
}

void copyArr(statistic_count dest[], statistic_count src[], int size) //function perpuse is to copy array.O(size)
{
	int i;
	for (i = NONE; i < size; i++)             //copy all arr into dest.
		dest[i] = src[i];
}

void color_card(player_data* player, int user_choice) //function perpuse is to handel color card.O(1)
{
	int color_choice;

	printf("Please enter your color choice:\n1 - Yellow\n2 - Red\n"
		"3 - Blue\n4 - Green\n");
	scanf("%d", &color_choice);
	pick_card_color(&player->player_cards[user_choice - ONE_IND], color_choice - ONE_IND);
}

bool plus_card(player_data* player, card* upper_card, statistic_count statistic[], int user_choice, bool finished_cards, int* diraction, int* player_index)//function perpuse is to handel plus card.O(players->number_of_cards)
{
	erase_card(player, upper_card, user_choice);
	if (player->num_of_cards == NONE)
		pick_card(player, statistic);
	else
		finished_cards = players_turn(player, upper_card, diraction, player_index, statistic);
	return finished_cards;
}

void free_dinamics(int player_ind, int number_of_players, player_data players[])	//function perpuse is to free all dinamic arrays.O(1)
{
	for (player_ind = NONE; player_ind < number_of_players; player_ind++)
		free(players[player_ind].player_cards);
	free(players);
}