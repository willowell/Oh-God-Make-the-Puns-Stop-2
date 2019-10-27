/*
 * Utilities.cpp
 *
 *  Created on: Oct. 7, 2019
 *      Author: whowell
 */

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "Utilities.h"

using namespace std;

namespace whowell {
	// Exceptions /////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	IntegerOutOfRangeException :: IntegerOutOfRangeException() {}

	IntegerOutOfRangeException :: ~IntegerOutOfRangeException() noexcept {}

	const char* IntegerOutOfRangeException :: what() const noexcept {
		return "Integer value out of range. Please try again.\n";
	}



	InvalidCharacterInputException :: InvalidCharacterInputException() {}

	InvalidCharacterInputException :: ~InvalidCharacterInputException() noexcept {}

	const char* InvalidCharacterInputException :: what() const noexcept {
		return "Invalid character. Please try again.\n";
	}



	InvalidStringLengthException :: InvalidStringLengthException() {}

	InvalidStringLengthException :: ~InvalidStringLengthException() noexcept {}

	const char* InvalidStringLengthException :: what() const noexcept {
		return "String too long. Please try again.\n";
	}



	NodeNotFoundException :: NodeNotFoundException() {}

	NodeNotFoundException :: ~NodeNotFoundException() noexcept {}

	const char* NodeNotFoundException :: what() const noexcept {
		return "Node not found in list.\n";
	}

	UnableToReserveASeatException :: UnableToReserveASeatException() {}

	UnableToReserveASeatException :: ~UnableToReserveASeatException() noexcept {}

	const char* UnableToReserveASeatException :: what() const noexcept {
		return "Unable to reserve seat.\n";
	}

	// List Modification Functions ////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
/*
	void performReservationsWithVectors( std::list<Seat>* list, Auditorium* auditorium,
					std::vector< short > rows, short tickets ) {
				std::string buffer;
				char yetAnotherUserChar;

				try {
					for ( short i = 0; i < tickets; i++ ) {
						if ( list->searchForNodeAndGetStatus(
							//assume all the seats are on the first selected row
							( auditorium->getNumRows() / 2 ),
							//then, look at the seat in the middle
							//and subtract half the number of tickets that the user selected
							//so that the middle ticket is exactly in the middle of the row
							( auditorium->getNumSeats() / 2 ) - ( tickets / 2 ) + i ) == true )
								throw UnableToReserveASeatException();
					} //close for-loop

					//If no exception has been thrown, then all of the seats are available
					//and can now be reserved.
					printf( "The seats in the middle of the row are available!\n" );
					printf( "Would you like to reserve them? (\"Y\" or \"N\")\n" );
					yetAnotherUserChar = validateStringAsCharacter( buffer, 'Y', 'N' );

					if ( toupper( yetAnotherUserChar ) == 'Y' ) {
						//Reserve the seats.
						//These should not throw an exception, but if they do,
						//it will be handled by the catch block below.
						for ( short j = 0; j < tickets; j++ )
							list->reserveASeatWithoutInput( auditorium, ( auditorium->getNumRows() / 2 ),
								                          ( auditorium->getNumSeats() / 2 ) - ( tickets / 2 ) + j );
						printf( "Seats reserved!\n" );

					} else if ( toupper( yetAnotherUserChar ) == 'N' )
						printf( "The seats will not be reserved.\n" );
				} catch ( UnableToReserveASeatException& e ) {
					std::cout << e.what() << '\n';
				} //close try-catch block
			}


	bool search_for_seat_and_get_status_from_list( std::list<Seat> from_list, int rowNum, int seatNum ) const {
		Node* current = head;
		try {
			if ( current->getRow() == rowNum && current->getSeat() == seatNum ) {
				//Then the first node is the one the user is looking for.
				//Return TRUE if it is RESERVED
				if ( current->isReserved() == true )
					return true;
				//Return FALSE if it is NOT RESERVED
				if ( current->isReserved() == false )
					return false;
			} else {
				//Cycle through the list.
				while ( current != nullptr ) {
					current = current->getNext();

					//Continue checking each node in the list.
					if ( current->getRow() == rowNum && current->getSeat() == seatNum ) {
						if ( current->isReserved() == true )
							return true;
						if ( current->isReserved() == false )
							return false;
					}
				}
			}
			//If the node still has not been found, then it probably isn't in the list.
			//Throw an exception
			throw NodeNotFoundException();
		} catch ( NodeNotFoundException& e ) {
			e.what();
			return true;
		}

	}

	Seat* search_for_and_get_seat_from_list( int rowNum, int seatNum ) {
		Node* current = head;
		Node* seek = nullptr;

		try {
			if ( current->getRow() == rowNum && current->getSeat() == seatNum ) {
				seek = current;
				return seek;
			} else {
				//Cycle through the list.
				while ( current != nullptr ) {
					current = current->getNext();

					//Continue checking each node in the list.
					if ( current->getRow() == rowNum && current->getSeat() == seatNum ) {
						seek = current;
						return seek;
					}
				}
			}
			//If the node still has not been found, then it probably isn't in the list.
			//Throw an exception
			throw NodeNotFoundException();
		} catch ( NodeNotFoundException& e ) {
			e.what();
			return nullptr;
		}
	}

	void reserve_a_seat( Auditorium* corresponding, int rowNum, int seatNum ) {
		std::string str;
		char userChar;

		if ( searchForNodeAndGetStatus( rowNum, seatNum ) == true )
			throw UnableToReserveASeatException();
		else {
			//Then the seat is available.
			std::cout << "The seat you have chosen is available!\n";
			std::cout << "Would you like to reserve it? (\"Y\" or \"N\")\n";
			userChar = validateStringAsCharacter( str, 'Y', 'N' );

			if ( toupper( userChar ) == 'Y' ) {
				std::cout << "I will reserve the seat for you.\n";
				searchForAndGetNode( rowNum, seatNum )->setReserved( true );
				std::cout << "The seat is now reserved!\n";
				corresponding->setNumSeatsReserved( corresponding->getNumSeatsReserved() + 1 );
				corresponding->setNumSeatsOpen( corresponding->getNumSeatsOpen() - 1 );

			} else if ( toupper( userChar ) == 'N' )
				std::cout << "The seat will not be reserved.\n";
		}
	}

	void reserve_a_seat_without_input( Auditorium* corresponding, int rowNum, int seatNum ) {
		if ( searchForNodeAndGetStatus( rowNum, seatNum ) == true )
			throw UnableToReserveASeatException();
		else {
			searchForAndGetNode( rowNum, seatNum )->setReserved( true );
			corresponding->setNumSeatsReserved( corresponding->getNumSeatsReserved() + 1 );
			corresponding->setNumSeatsOpen( corresponding->getNumSeatsOpen() - 1 );
		}
	}

*/
    // Validation Functions ///////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////

	short int validate_string_as_single_digit_integer_in_range( std::string buffer, short int min, short int max ) {
		std::string::size_type sz = 0;
		short int user_short = 0;

		while (true) {
			try {
				std::cin >> buffer;

				if ( buffer.length() != 1 ) {
					std::cout << "Please enter only one character!" << std::endl;
					continue;
				}

				if ( !isdigit( buffer.at( 0 ) ) ) {
					std::cout << "Please enter only a number!" << std::endl;
					continue;
				}

				//Now, convert the string to an integer, store it in user_short
				//Then, check that the value is within the expected range
				user_short = std::stoi( buffer, &sz );

				if ( user_short < min || user_short > max ) {
					std::cout << "Please enter a number between " << min << " and " << max << '!' << std::endl;
					continue;
				}

				//If no exception has been thrown by this point, then the input is valid.
				break;
			} catch ( ... ) {
				std::cerr << "Some other exception has occurred. Your input was: [" << buffer << "]." << std::endl;
			}
		}

		return user_short;
	}

	short int validate_string_as_double_digit_integer_in_range( std::string buffer, short int min, short int max ) {
		std::string::size_type sz = 0;
		short int user_short = 0;

		while (true) {
			try {
				std::cin >> buffer;

				if ( buffer.length() != 2 ) {
					std::cout << "Please enter only one double digit number!" << std::endl;
					continue;
				}

				if ( !isdigit( buffer.at( 0 ) ) || !isdigit( buffer.at( 1 ) ) ) {
					std::cout << "Please enter only a number!" << std::endl;
					continue;
				}

				//Now, convert the string to an integer, store it in userShort
				//Then, check that the value is within the expected range
				user_short = std::stoi( buffer, &sz );

				if ( user_short < min || user_short > max ) {
					std::cout << "Please enter a number between " << min << " and " << max << '!' << std::endl;
					continue;
				}

				//If no exception has been thrown by this point, then the input is valid.
				break;
			} catch ( ... ) {
				std::cerr << "Some other exception has occurred. Your input was: [" << buffer << "]." << std::endl;
			}
		}

		return user_short;
	}

	char validate_string_as_character(std::string buffer, char upper_case_character) {
		char user_char = '\n';

		while (true) {
			try {
				std::cin >> buffer;

				if ( buffer.length() != 1 ) {
					std::cout << "Please enter only one character!" << std::endl;
					continue;
				}

				//Now, convert the string to an integer, store it in userShort
				//Then, check that the value is within the expected range
				user_char = buffer.at(0);

				if ( toupper( user_char ) == upper_case_character ) {
					break;

				} else {
					std::cout << "Please enter another character!" << std::endl;
					continue;
				}

			} catch ( ... ) {
				std::cerr << "Some other exception has occurred. Your input was: [" << buffer << "]." << std::endl;
			}
		}

		return toupper( user_char );
	}

	bool yes_or_no_prompt( std::string prompt ) {
		std::string buffer;
		char answer = 'a';
		do {
			std::cout << prompt << std::endl;
			std::cin >> buffer;

			if ( buffer.length() != 1 ) {
				std::cout << "Please enter only one character!" << std::endl;
				continue;
			}

			answer = toupper( buffer.at( 0 ) );

			if ( answer != 'Y' && answer != 'N' ) {
				std::cout << "Please enter only 'y' or 'n'!" << std::endl;
			}
		} while ( answer != 'Y' && answer != 'N' );

		return ( answer == 'Y' );
	}

} /* namespace whowell */
