# Bus_reservation
A bus counter management text-based software
Program Documentation: Bus Reservation System
1. Introduction
This C program implements a bus seat reservation system. It provides features such as booking seats, canceling bookings, showing available trips, displaying all passenger bookings, and more. The program handles routes from Dhaka to four destinations: Sylhet, Chattogram, Khulna, and Rajshahi.
2. Features
•	Display available trips with fare and time.
•	Book seats for a trip.
•	Cancel a seat reservation.
•	Show individual passenger information based on seat number.
•	View all bookings made for all trips.
•	Display seat pattern of the bus.
3. Program Structure
The program consists of the following modules:
3.1 Main Menu
The program displays a menu offering various operations. The user is prompted to select an action:
1.	Show available trips
2.	Book a seat
3.	Cancel a booking
4.	Show passenger info
5.	Show all bookings
6.	Show seat pattern
7.	Exit
3.2 Data Handling
Passenger and booking data are stored in text files, created for each destination based on the current date. The files store seat numbers, passenger names, phone numbers, departure location, destination, and booking time.
4. Functions
4.1 welcome_screen()
Displays the welcome screen and prompts the user for a password to access the system. The default password is "whoami". Incorrect attempts require re-entry.
4.2 file_handling()
Initializes file handling for the four destination routes. If the files are empty, they are initialized with a header line.
4.3 main_menu()
Displays the main menu and waits for user input to choose an option.
4.4 show_available_trips()
Displays the currently available trips with their destination, fare, and departure time.
4.5 book_a_seat()
Allows the user to book one or more seats for a selected trip. The user provides their name, mobile number, and desired seat numbers. The system checks seat availability before confirming the booking.
4.6 cancel_a_booking()
Enables users to cancel an existing booking by providing the trip number and seat number. The system confirms the cancellation before proceeding.
4.7 show_passenger_info()
Displays the passenger details for one or more seat numbers on a selected trip.
4.8 show_all_bookings()
Prints all bookings made for every trip.
4.9 show_seat_pattern()
Displays a visual pattern of available and booked seats for the bus.
5. Additional Functions
•	get_booking(int trip): Handles the booking process for a trip.
•	check_existing(int trip, char seat_no[3]): Checks if a seat is already booked for a trip.
•	seat_validity(int i): Validates if a seat number is correct.
6. Enum & Data Structures
6.1 enum destination
Represents the four possible destinations: Sylhet, Chattogram, Khulna, Rajshahi.
6.2 struct passenger_info
Contains the passenger's details, including:
•	seat_quantity: Number of seats booked.
•	seat_no[5][3]: Array to store up to 5 seat numbers.
•	name[20]: Passenger's name.
•	mobile: Passenger's mobile number.
7. File Storage
The program creates a text file for each destination trip, named using the format:
php
Copy code
dhaka2<destination>-<date>.txt
Each file logs the seat number, passenger details, departure, destination, and time of booking.
8. Error Handling
•	Validates seat number entries to ensure they are within valid seat ranges.
•	Confirms availability of seats before booking.
•	Handles incorrect inputs during trip selection and seat number input.
9. Conclusion
This Bus Reservation System allows users to easily manage bus bookings between Dhaka and several destinations. It includes essential functionalities like booking, canceling, and displaying reservation information, making it a practical tool for managing bus reservations.

