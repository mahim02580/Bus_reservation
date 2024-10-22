#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define DEPARTURE "Dhaka"
#define MAX 102

void welcome_screen();
void file_handling();
void main_menu();
void show_available_trips();
void book_a_seat();
void cancel_a_booking();
void show_passenger_info();
void show_all_bookings();
void show_seat_pattern();
void get_booking(int);
int check_existing(int, char seat_no[3]);
int seat_validity(int);

enum destination
{
    sylhet,
    chattagram,
    khulna,
    rajshahi
} e_destination;

struct passenger_info
{
    int seat_quantity;
    char seat_no[5][3];
    char name[20];
    long mobile;
} passenger;

FILE *dh2d[4];

char *filename[4] = {"dhaka2sylhet-"__DATE__
                     ".txt",
                     "dhaka2chattogram-"__DATE__
                     ".txt",
                     "dhaka2khulna-"__DATE__
                     ".txt",
                     "dhaka2rajshahi-"__DATE__
                     ".txt"};
int main()
{
    welcome_screen();
    file_handling();
    while (1)
    {
        main_menu();

        printf("\t\t\t\t\t\tEnter your choice (0 to exit) >>");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            exit(1);
            break;
        case 1:
            show_available_trips();
            printf("\t\t\t\t\t\t    Press enter to main menu......");
            getchar();
            getchar();
            system("cls");
            break;
        case 2:
            book_a_seat();
            break;
        case 3:
            cancel_a_booking();
            break;
        case 4:
            show_passenger_info();
            break;
        case 5:
            show_all_bookings();
            break;
        case 6:
            show_seat_pattern();
            printf("\n\t\t\t\t\t\t            Press enter to continue......");
            getchar();
            getchar();
            system("cls");
            break;
        default:
            system("cls");
            printf("\n\t\t\t\t\t\t    Invalid Choice! Choose again(0 to exit)\n");
            break;
        }
    }
}
void welcome_screen()
{
    printf("\t\t\t\t\t\t****************************************************\n");
    printf("\t\t\t\t\t\t*                                                  *\n");
    printf("\t\t\t\t\t\t*                                                  *\n");
    printf("\t\t\t\t\t\t*            **************************            *\n");
    printf("\t\t\t\t\t\t*            *         Welcome        *            *\n");
    printf("\t\t\t\t\t\t*            *           To           *            *\n");
    printf("\t\t\t\t\t\t*            * Whoami Bus Reservation *            *\n");
    printf("\t\t\t\t\t\t*            **************************            *\n");
    printf("\t\t\t\t\t\t*                                                  *\n");
    printf("\t\t\t\t\t\t*                                                  *\n");
    printf("\t\t\t\t\t\t****************************************************\n");

    char password[7];

    while (1)
    {
        printf("\n\t\t\t\t\t\t             Enter password: ");
        scanf("%s", password);

        if (strcmp(password, "whoami"))
        {
            printf("\n\t\t\t\t\t\t             Wrong password! Try again\n");
        }
        else
        {
            system("cls");
            printf("\n\t\t\t\t\t\t                 Log in successful!\n");
            break;
        }
    }
}
void file_handling()
{
    for (int i = 0; i < 4; i++)
    {
        dh2d[i] = fopen(filename[i], "a+");
        if (getc(dh2d[i]) == EOF)
        {
            fprintf(dh2d[i], "Seat_No.%-4cPassenger Name%-6cMobile%-10cDeparture%-7cDestination%-9cDate & Time\n", ' ', ' ', ' ', ' ', ' ');
            fprintf(dh2d[i], "----------------------------------------------------------------------------------------------------\n");
            fflush(dh2d[i]);
        }
    }
}
void main_menu()
{
    printf("\n\t\t\t\t\t\t*           #Choose an option-                     *\n");
    printf("\t\t\t\t\t\t*              1. Show Available Trips             *\n");
    printf("\t\t\t\t\t\t*              2. Book a seat                      *\n");
    printf("\t\t\t\t\t\t*              3. Cancel a booking                 *\n");
    printf("\t\t\t\t\t\t*              4. Show passnager info              *\n");
    printf("\t\t\t\t\t\t*              5. Show all bookings                *\n");
    printf("\t\t\t\t\t\t*              6. Show seat pattern                *\n");
}
void show_available_trips()
{
    system("cls");
    printf("\t\t\t\t\t\t\t        #Currently available: \n");
    printf("\t\t\t\t\t\t\t        `````````````````````\n");
    printf("\t\t\t\t\t\t           Trips               Fair        Time\n");
    printf("\t\t\t\t\t\t    1. Dhaka to Sylhet       BDT 1000    09.00 AM\n");
    printf("\t\t\t\t\t\t    2. Dhaka to Chattogram   BDT 1000    12.00 PM\n");
    printf("\t\t\t\t\t\t    3. Dhaka to Khulna       BDT 1000    03.00 PM\n");
    printf("\t\t\t\t\t\t    4. Dhaka to Rajshahi     BDT 1000    09.00 PM\n\n");
}
void book_a_seat()
{
    int choice_book_a_seat;
    system("cls");

    show_available_trips();

    while (1)
    {
        printf("\t\t\t\t\t\t    Enter your choice (0 to main menu) >>");
        scanf("%d", &choice_book_a_seat);

        if ((1 <= choice_book_a_seat) && (choice_book_a_seat <= 4))
        {
            get_booking(choice_book_a_seat);
            break;
        }
        else if (choice_book_a_seat == 0)
        {
            system("cls");
            break;
        }
        else
        {
            printf("\n\t\t\t\t\t\t             Invalid Choice! Choose again\n\n");
        }
    }
}
void cancel_a_booking()
{
    FILE *temp = fopen("temp.txt", "w");

    char passanger_info[MAX], seat[3], ch, temp_line[MAX];
    int trip, found = 0;

    system("cls");
    show_available_trips();

    while (1)
    {
        printf("\t\t\t\t\t\t          Select trip to cancel a ticket: ");
        scanf("%d", &trip);
        getchar();
        if ((trip < 1) || (trip > 4))
        {
            printf("\n\t\t\t\t\t\t\t          Enter a valid trip!\n\n");
            continue;
        }
        break;
    }

    while (1)
    {
        printf("\n\t\t\t\t\t\t             Enter seat number: ");
        fgets(passenger.seat_no[0], 3, stdin);
        getchar();
        if (!seat_validity(0))
        {
            printf("\n\t\t\t\t\t\t\t Error! Enter a valid seat number...\n");
            continue;
        }
        break;
    }

    rewind(dh2d[(trip - 1)]);

    while (!feof(dh2d[(trip - 1)]))
    {
        fscanf(dh2d[(trip - 1)], "%s", passanger_info);
        if (strcmp(strupr(passenger.seat_no[0]), passanger_info) == 0)
        {
            fseek(dh2d[(trip - 1)], -2, SEEK_CUR);
            fgets(passanger_info, sizeof(passanger_info), dh2d[(trip - 1)]);
            printf("Preview:\n\nSeat_No.%-4cPassenger Name%-6cMobile%-10cDeparture%-7cDestination%-9cDate & Time\n", ' ', ' ', ' ', ' ', ' ');
            printf("----------------------------------------------------------------------------------------------------\n");
            printf("%s", passanger_info);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        system("cls");
        printf("\n\t\t\t\t\t\t\t       Seat not booked yet!\n");
        fclose(temp);
        remove("temp.txt");
        return;
    }

    printf("\nAre you sure want to cancel your booking?(y/n): ");
    ch = getchar();
    if (toupper(ch) == 'Y')
    {
        rewind(dh2d[(trip - 1)]);

        while (fgets(temp_line, sizeof(temp_line), dh2d[(trip - 1)]) != '\0')
        {
            if (strcmp(temp_line, passanger_info) == 0)
            {
                fgets(temp_line, sizeof(temp_line), dh2d[(trip - 1)]);
                continue;
            }
            else
            {
                fprintf(temp, "%s", temp_line);
            }
        }

        fclose(temp);
        fclose(dh2d[(trip - 1)]);

        remove(filename[trip - 1]);
        rename("temp.txt", filename[trip - 1]);

        dh2d[(trip - 1)] = fopen(filename[trip - 1], "a+");

        system("cls");
        printf("\n\t\t\t\t\t\t\t       Successfully Canceled!\n");
    }
    else
    {
        fclose(temp);
        remove("temp.txt");
        system("cls");
    }
}
void show_passenger_info()
{
    int seat_quantity, trip, flag = 0;
    char seat[MAX], passenger_info_print[MAX];
    show_available_trips();

    while (1)
    {
        printf("\t\t\t\t\t\t\tSelect trip to get passenger info: ");
        scanf("%d", &trip);
        if ((trip < 1) || (trip > 4))
        {
            printf("\n\t\t\t\t\t\t\t         Enter a valid trip!\n\n");
            continue;
        }
        break;
    }
    while (1)
    {
        printf("\n\t\t\t\t\t\t\tHow many seats? (max 45): ");
        scanf("%d", &seat_quantity);
        getchar();
        if (seat_quantity < 1 || seat_quantity > 45)
        {
            printf("\n\t\t\t\t\t\t\t         Min 1 & Max 45\n");
            continue;
        }
        break;
    }

    for (int i = 0; i < seat_quantity; i++)
    {
        while (1)
        {
            printf("\t\t\t\t\t\t\tEnter Seat No[%d]: ", i + 1);
            fgets(passenger.seat_no[i], 3, stdin);
            getchar();
            if (!seat_validity(i))
            {
                printf("\n\t\t\t\t\t\t\t       Error! Enter a valid seat number...\n\n");
                continue;
            }
            break;
        }
    }

    system("cls");
    printf("Seat_No.%-4cPassenger Name%-6cMobile%-10cDeparture%-7cDestination%-9cDate & Time\n", ' ', ' ', ' ', ' ', ' ');

    for (int i = 0; i < seat_quantity; i++)
    {
        flag = 0;
        rewind(dh2d[(trip - 1)]);
        while (!feof(dh2d[(trip - 1)]))
        {
            fscanf(dh2d[(trip - 1)], "%s", seat);
            if (strcmp(seat, strupr(passenger.seat_no[i])) == 0)
            {
                printf("----------------------------------------------------------------------------------------------------\n");
                printf("%s", seat);
                fscanf(dh2d[(trip - 1)], "%[^\n]", seat);
                printf("%s\n", seat);
                flag = 1;
            }
        }
        if ((feof(dh2d[(trip - 1)])) && (flag == 0))
        {
            printf("\n\t\t\t\t\tNot found\n");
        }
    }
    printf("Press enter to continue......");
    getchar();
    system("cls");
}
void show_all_bookings()
{
    char passenger_info_print[MAX];
    system("cls");

    for (int i = 0; i < 4; i++)
    {
        rewind(dh2d[i]);
        while ((fgets(passenger_info_print, sizeof(passenger_info_print), dh2d[i])))
        {
            printf("%s", passenger_info_print);
        }
        printf("\n\n");
    }
    printf("\nPress enter to continue......");
    getchar();
    getchar();
    system("cls");
}
void show_seat_pattern()
{
    system("cls");
    char seat_series;

    for (seat_series = 'A'; seat_series <= 'K'; seat_series++)
    {
        printf("\n\t\t\t\t\t\t\t\t    ");
        for (int i = 1; i <= 4; i++)
        {
            if (i == 3 && seat_series != 'K')
            {
                printf("   ");
            }
            printf("%c%d ", seat_series, i);
        }
    }
    printf("K5\n");
}
void get_booking(int trip)
{
    char *destination;

    if (trip == 1)
    {
        destination = "Sylhet";
        e_destination = sylhet;
    }
    else if (trip == 2)
    {
        destination = "Chattogram";
        e_destination = chattagram;
    }
    else if (trip == 3)
    {
        destination = "Khulna";
        e_destination = khulna;
    }
    else if (trip == 4)
    {
        destination = "Rajshahi";
        e_destination = rajshahi;
    }

    while (1)
    {
        printf("\n\t\t\t\t\t\t    Enter seat quantity (max 45): ");
        scanf("%d", &passenger.seat_quantity);
        getchar();

        if (passenger.seat_quantity < 1 || passenger.seat_quantity > 45)
        {
            printf("\n\t\t\t\t\t\t\tMin 1 seat & Max 45 seats!\n");
            continue;
        }
        break;
    }

    system("cls");

    char seat_series[3] = "A1";

    for (int i = 0; seat_series[i] <= 'K'; seat_series[i]++)
    {
        printf("\n\t\t\t\t\t\t\t\t    ");
        for (seat_series[1] = '1'; seat_series[1] <= '4'; seat_series[1]++)
        {
            if (seat_series[1] == '3' && seat_series[i] != 'K')
            {
                printf("   ");
            }
            if (check_existing(trip, seat_series))
            {
                printf("\033[31m%s ", seat_series);
            }
            else
            {
                printf("\033[0m%s ", seat_series);
            }
        }
    }
    if (check_existing(trip, "K5"))
    {
        printf("\033[31mK5\033[0m\n\n");
    }
    else
    {
        printf("\033[0mK5\n\n");
    }

    for (int i = 0; i < passenger.seat_quantity; i++)
    {
        while (1)
        {
            printf("\t\t\t\t\t\t\t       Enter seat number [%d]: ", i + 1);
            scanf("%[^\n]", passenger.seat_no[i]);
            getchar();
            if (check_existing(trip, passenger.seat_no[i]))
            {
                printf("\n\t\t\t\t\t\t\t       This seat already booked!");
                printf("\n\t\t\t\t\t\t\t       Choose another one......\n\n");
                continue;
            }
            if (!seat_validity(i))
            {
                printf("\n\t\t\t\t\t\t\t       Error! Enter a valid seat number...\n\n");
                continue;
            }
            break;
        }
    }
    printf("\n\t\t\t\t\t\t\t       Enter Passenger Name: ");
    scanf("%[^\n]", passenger.name);
    getchar();

    printf("\t\t\t\t\t\t\t       Enter Passanger mobile number: 01");
    scanf("%ld", &passenger.mobile);
    getchar();

    for (int i = 0; i < passenger.seat_quantity; i++)
    {
        fprintf(dh2d[e_destination], "%-12s%-20s01%-14ld%-16s%-14s\t%-s|%-s\n", strupr(passenger.seat_no[i]), passenger.name, passenger.mobile, DEPARTURE, destination, __DATE__, __TIME__);
        fprintf(dh2d[e_destination], "----------------------------------------------------------------------------------------------------\n");
        fflush(dh2d[e_destination]);
    }
    system("cls");
    printf("\n\t\t\t\t\t\t\t        Booking successful!\n");
}
int check_existing(int trip, char seat_no[3])
{
    char seat[200];
    rewind(dh2d[(trip - 1)]);
    while (!feof(dh2d[(trip - 1)]))
    {
        fscanf(dh2d[(trip - 1)], "%s", seat);
        if (strcmp(seat, strupr(seat_no)) == 0)
        {
            return 1;
        }
    }
    return 0;
}
int seat_validity(int i)
{
    if (toupper(passenger.seat_no[i][0]) == 'K' && passenger.seat_no[i][1] == '5')
    {
        return 1;
    }
    else if (!(toupper(passenger.seat_no[i][0]) >= 'A' && toupper(passenger.seat_no[i][0]) <= 'K' && passenger.seat_no[i][1] >= '1' && passenger.seat_no[i][1] <= '4'))
    {
        return 0;
    }
    return 1;
}
