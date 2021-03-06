/*
 * Seat.h
 *
 *  Created on: Oct. 7, 2019
 *      Author: Whowell
 */

#ifndef OHGODMAKETHEPUNSSTOP_VERSION_2_SEAT_H
#define OHGODMAKETHEPUNSSTOP_VERSION_2_SEAT_H

namespace Whowell {
	
	class Seat {
	private:
		int row; //(y)
		int column; //(x)
		bool is_reserved;
	public:
		Seat();
		
		Seat(int row_num, int column_num, bool seat_state);
		
		virtual ~Seat();
		
		[[nodiscard]] int get_row() const;
		
		[[nodiscard]] int get_column() const;
		
		[[nodiscard]] bool is_seat_reserved() const;
		
		void set_row(int row_num);
		
		void set_column(int column_num);
		
		void set_reserved(bool seat_state);
		
		void display() const; //For debug/tracking
		
		// Do not worry about whether or not the seat is reserved when comparing seats.
		// The seat's position is enough to tell it apart from another seat.
		bool operator==(const Seat & seat) const {
			return ((get_row() == seat.get_row()) &&
					(get_column() == seat.get_column())
			);
		}
	};
	
} /* namespace Whowell */

#endif /*OHGODMAKETHEPUNSSTOP_VERSION_2_SEAT_H*/
