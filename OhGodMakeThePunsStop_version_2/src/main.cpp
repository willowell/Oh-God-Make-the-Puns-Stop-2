//============================================================================
// Name        : OhGodMakeThePunsStop_version_2.cpp
// Author      : wphowell
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include <boost/format.hpp>

#include "Auditorium.h"
#include "Seat.h"
#include "SeatList.h"
#include "Theatre.h"
#include "Utilities.h"


using namespace std;
using namespace whowell;

int main() {
	cout << boost::format("!!!Hello %1%!!!") % __func__ << endl; // prints !!!Hello World!!!

	bool is_debug = true;

	std::fstream      file_1;
	std::fstream      file_2;
	std::fstream      file_3;
	Auditorium        auditorium_1;
	Auditorium        auditorium_2;
	Auditorium        auditorium_3;
	Theatre           theatre;

	/// User input

	short int user_short = 0;
	short int user_selected_tickets = 0;
	short int user_choice = 0;
	char user_char = 'a';
	bool user_wants_to_quit = false;
	std::string buffer;
	std::vector < short int > user_selected_seats;
	std::vector < short int > user_selected_rows;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///INIT PHASE

	try {
		file_1 = std::fstream( "A1.txt", std::ios::in );
		file_2 = std::fstream( "A2.txt", std::ios::in );
		file_3 = std::fstream( "A3.txt", std::ios::in );
	} catch (...) {
		std::cerr << "Something went wrong with the files!" << std::endl;
		return EXIT_FAILURE;
	}

	auditorium_1.set_auditorium_id(1);
	auditorium_2.set_auditorium_id(2);
	auditorium_3.set_auditorium_id(3);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///LOAD PHASE

	auditorium_1.load_from_file(file_1);
	auditorium_2.load_from_file(file_2);
	auditorium_3.load_from_file(file_3);

    //Close the input files - they aren't needed until the end of the program.
    file_1.close();
    file_2.close();
    file_3.close();

    if (is_debug) {
    	auditorium_1.display();
    	auditorium_1.display_list();

    	auditorium_2.display();
    	auditorium_2.display_list();

    	auditorium_3.display();
    	auditorium_3.display_list();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///MAIN LOOP

    do {
    	user_short = -1;
    	user_choice = -1;

    	std::cout << "Please enter a number corresponding to a menu item.\n"
    			  << "(1) View an auditorium.\n"
				  << "(2) Make a reservation.\n"
				  << "(3) Print a sales report.\n"
				  << "(4) Save and quit."
    			  << std::endl;

    	user_short = validate_string_as_single_digit_integer_in_range( buffer, 1, 4 );
    	user_choice = user_short;

    	switch ( user_choice ) {
			case 1: {
				user_short = -1;

				std::cout << "Please enter the number of the auditorium you wish to view.\n"
						  << "You can choose Auditorium (1), (2), or (3).\n"
						  << std::endl;

				user_short = validate_string_as_single_digit_integer_in_range( buffer, 1, 3 );

				switch ( user_short ) {
					case 1: {
						auditorium_1.display_grid();
						break;
					}
					case 2: {
						auditorium_2.display_grid();
						break;
					}
					case 3: {
						auditorium_3.display_grid();
						break;
					}
					default: {
						std::cerr << "This should be unreachable!\n"
								  << "(short int) user_short is " << user_short
								  << std::endl;
						break;
					}
				}

				break;
			} // END CASE 1 ****************************************************


			case 2: {
				break;
			}


			case 3: {
				break;
			}


			case 4: {
				user_wants_to_quit = yes_or_no_prompt(
						"Are you sure you want to quit? [y/n]\nChanges to the data will be saved."
				);

				if (user_wants_to_quit) {
					std::cout << "Quitting the program.\n"
							  << "Please wait while the data is saved." << std::endl;
				} else {
					std::cout << "Returning to the main menu." << std::endl;
				}
				break;
			}


			default: {
				std::cerr << "This should be unreachable!\n"
						  << "(short int) user_choice is " << user_choice
						  << std::endl;
				break;
			}
    	}

    } while (!user_wants_to_quit);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///FILE OUTPUT

    std::cout << "Exiting." << std::endl;
	return EXIT_SUCCESS;
}
