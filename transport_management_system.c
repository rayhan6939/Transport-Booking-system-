#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Structure definitions
typedef struct
{
    int id;
    char type[20];
    int capacity;
    char registration[20];
} Vehicle;

typedef struct
{
    int id;
    char source[50];
    char destination[50];
    float distance;
    float fare_per_km;
} Route;

typedef struct
{
    int id;
    int vehicle_id;
    int route_id;
    char departure_time[20];
    char arrival_time[20];
    int available_seats;
} Trip;

typedef struct
{
    int id;
    int trip_id;
    char passenger_name[50];
    int seat_number;
    time_t booking_time;
    float fare_paid;
} Booking;

// Global variables
Vehicle vehicles[100];
Route routes[100];
Trip trips[100];
Booking bookings[1000];

int vehicle_count = 0;
int route_count = 0;
int trip_count = 0;
int booking_count = 0;

// Function prototypes
void load_data();
void save_data();
void admin_menu();
void user_menu();
void manage_vehicles();
void manage_routes();
void manage_trips();
void view_bookings();
void book_ticket();
void cancel_ticket();
void view_available_trips();
void display_trip_details(int trip_id);
float calculate_fare(int route_id, int seat_count);
int find_available_seat(int trip_id);

// Main function
int main()
{
    load_data();

    int choice;
    do
    {
        printf("\n\n~~~ Transport Booking System ~~~\n");
        printf("1. Administrator Login\n");
        printf("2. User Menu\n");
        printf("3. Exit\n");
        printf("Enter your choice: :)\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            admin_menu();
            break;
        case 2:
            user_menu();
            break;
        case 3:
            save_data();
            printf("Exiting system. Data saved Have a Good day Sir.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}

// Load data from files
void load_data()
{
    FILE *file;

    // Load vehicles
    file = fopen("vehicles.dat", "rb");
    if (file != NULL)
    {
        vehicle_count = fread(vehicles, sizeof(Vehicle), 100, file);
        fclose(file);
    }

    // Load routes
    file = fopen("routes.dat", "rb");
    if (file != NULL)
    {
        route_count = fread(routes, sizeof(Route), 100, file);
        fclose(file);
    }

    // Load trips
    file = fopen("trips.dat", "rb");
    if (file != NULL)
    {
        trip_count = fread(trips, sizeof(Trip), 100, file);
        fclose(file);
    }

    // Load bookings
    file = fopen("bookings.dat", "rb");
    if (file != NULL)
    {
        booking_count = fread(bookings, sizeof(Booking), 1000, file);
        fclose(file);
    }
}

// Save data to files
void save_data()
{
    FILE *file;

    // Save vehicles
    file = fopen("vehicles.dat", "wb");
    if (file != NULL)
    {
        fwrite(vehicles, sizeof(Vehicle), vehicle_count, file);
        fclose(file);
    }

    // Save routes
    file = fopen("routes.dat", "wb");
    if (file != NULL)
    {
        fwrite(routes, sizeof(Route), route_count, file);
        fclose(file);
    }

    // Save trips
    file = fopen("trips.dat", "wb");
    if (file != NULL)
    {
        fwrite(trips, sizeof(Trip), trip_count, file);
        fclose(file);
    }

    // Save bookings
    file = fopen("bookings.dat", "wb");
    if (file != NULL)
    {
        fwrite(bookings, sizeof(Booking), booking_count, file);
        fclose(file);
    }
}

// Administrator menu
void admin_menu()
{
    char username[20], password[20];
    printf("\nAdmin Login\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    // Simple authentication (in real system, use secure methods)
    if (strcmp(username, "DIU") != 0 || strcmp(password, "rayhan123") != 0)
    {
        printf("Invalid credentials!\n");
        return;
    }

    int choice;
    do
    {
        printf("\n=== Administrator Menu ===\n");
        printf("1. Manage Vehicles\n");
        printf("2. Manage Routes\n");
        printf("3. Manage Trips\n");
        printf("4. View Bookings\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            manage_vehicles();
            break;
        case 2:
            manage_routes();
            break;
        case 3:
            manage_trips();
            break;
        case 4:
            view_bookings();
            break;
        case 5:
            printf("Returning to main menu.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}

// User menu
void user_menu()
{
    int choice;
    do
    {
        printf("\n=== User Menu ===\n");
        printf("1. View Available Trips\n");
        printf("2. Book Ticket\n");
        printf("3. Cancel Ticket\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            view_available_trips();
            break;
        case 2:
            book_ticket();
            break;
        case 3:
            cancel_ticket();
            break;
        case 4:
            printf("Returning to main menu.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

// Manage vehicles
void manage_vehicles()
{
    int choice;
    do
    {
        printf("\n=== Vehicle Management ===\n");
        printf("1. Add New Vehicle\n");
        printf("2. View All Vehicles\n");
        printf("3. Back to Admin Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            if (vehicle_count >= 100)
            {
                printf("Maximum vehicle limit reached!\n");
                break;
            }

            Vehicle v;
            v.id = vehicle_count + 1;

            printf("\nEnter Vehicle Type (e.g., Bus, Minibus): ");
            scanf("%s", v.type);
            printf("Enter Vehicle Capacity: ");
            scanf("%d", &v.capacity);
            printf("Enter Registration Number: ");
            scanf("%s", v.registration);

            vehicles[vehicle_count++] = v;
            printf("Vehicle added successfully!\n");
            break;
        }
        case 2:
        {
            printf("\n*~* Vehicle List *~*\n");
            printf("ID\tType\t\tCapacity\tRegistration\n");
            for (int i = 0; i < vehicle_count; i++)
            {
                printf("%d\t%s\t\t%d\t\t%s\n",
                       vehicles[i].id, vehicles[i].type,
                       vehicles[i].capacity, vehicles[i].registration);
            }
            break;
        }
        case 3:
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

// Manage routes
void manage_routes()
{
    int choice;
    do
    {
        printf("\n=== Route Management ===\n");
        printf("1. Add New Route\n");
        printf("2. View All Routes\n");
        printf("3. Update Route Fare\n");
        printf("4. Back to Admin Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            if (route_count >= 100)
            {
                printf("Maximum route limit reached!\n");
                break;
            }

            Route r;
            r.id = route_count + 1;

            printf("\nEnter Source: ");
            scanf("%s", r.source);
            printf("Enter Destination: ");
            scanf("%s", r.destination);
            printf("Enter Distance (km): ");
            scanf("%f", &r.distance);
            printf("Enter Fare per KM: ");
            scanf("%f", &r.fare_per_km);

            routes[route_count++] = r;
            printf("Route added successfully!\n");
            break;
        }
        case 2:
        {
            printf("\n=== Route List ===\n");
            printf("ID\tSource\t\tDestination\tDistance\tFare/KM\n");
            for (int i = 0; i < route_count; i++)
            {
                printf("%d\t%s\t\t%s\t\t%.2f\t\t%.2f\n",
                       routes[i].id, routes[i].source,
                       routes[i].destination, routes[i].distance,
                       routes[i].fare_per_km);
            }
            break;
        }
        case 3:
        {
            int route_id;
            printf("Enter Route ID to update fare: ");
            scanf("%d", &route_id);

            int found = 0;
            for (int i = 0; i < route_count; i++)
            {
                if (routes[i].id == route_id)
                {
                    printf("Current fare per km: %.2f\n", routes[i].fare_per_km);
                    printf("Enter new fare per km: ");
                    scanf("%f", &routes[i].fare_per_km);
                    printf("Fare updated successfully!\n");
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                printf("Route not found!\n");
            }
            break;
        }
        case 4:
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

// Manage trips
void manage_trips()
{
    int choice;
    do
    {
        printf("\n~*~ Trip Management ~*~ \n");
        printf("1. Schedule New Trip\n");
        printf("2. View All Trips\n");
        printf("3. Cancel Trip\n");
        printf("4. Back to Admin Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            if (trip_count >= 100)
            {
                printf("Maximum trip limit reached!\n");
                break;
            }

            Trip t;
            t.id = trip_count + 1;

            printf("\nAvailable Vehicles:\n");
            for (int i = 0; i < vehicle_count; i++)
            {
                printf("%d. %s (%s, Capacity: %d)\n",
                       vehicles[i].id, vehicles[i].type,
                       vehicles[i].registration, vehicles[i].capacity);
            }
            printf("Select Vehicle ID: ");
            scanf("%d", &t.vehicle_id);

            printf("\nAvailable Routes:\n");
            for (int i = 0; i < route_count; i++)
            {
                printf("%d. %s to %s (%.2f km)\n",
                       routes[i].id, routes[i].source,
                       routes[i].destination, routes[i].distance);
            }
            printf("Select Route ID: ");
            scanf("%d", &t.route_id);

            printf("Enter Departure Time (HH:MM): ");
            scanf("%s", t.departure_time);
            printf("Enter Arrival Time (HH:MM): ");
            scanf("%s", t.arrival_time);

            // Find vehicle capacity
            for (int i = 0; i < vehicle_count; i++)
            {
                if (vehicles[i].id == t.vehicle_id)
                {
                    t.available_seats = vehicles[i].capacity;
                    break;
                }
            }

            trips[trip_count++] = t;
            printf("Trip scheduled successfully!\n");
            break;
        }
        case 2:
        {
            printf("\n~*~ Trip Schedule ~*~\n");
            printf("ID\tVehicle\tRoute\t\tDeparture\tArrival\tAvailable\n");
            for (int i = 0; i < trip_count; i++)
            {
                // Get vehicle info
                char vehicle_info[30] = "N/A";
                for (int j = 0; j < vehicle_count; j++)
                {
                    if (vehicles[j].id == trips[i].vehicle_id)
                    {
                        sprintf(vehicle_info, "%s", vehicles[j].type);
                        break;
                    }
                }

                // Get route info
                char route_info[50] = "N/A";
                for (int j = 0; j < route_count; j++)
                {
                    if (routes[j].id == trips[i].route_id)
                    {
                        sprintf(route_info, "%s-%s", routes[j].source, routes[j].destination);
                        break;
                    }
                }

                printf("%d\t%s\t%s\t%s\t%s\t%d\n",
                       trips[i].id, vehicle_info, route_info,
                       trips[i].departure_time, trips[i].arrival_time,
                       trips[i].available_seats);
            }
            break;
        }
        case 3:
        {
            int trip_id;
            printf("Enter Trip ID to cancel: ");
            scanf("%d", &trip_id);

            int found = 0;
            for (int i = 0; i < trip_count; i++)
            {
                if (trips[i].id == trip_id)
                {
                    // Remove the trip by shifting array
                    for (int j = i; j < trip_count - 1; j++)
                    {
                        trips[j] = trips[j + 1];
                    }
                    trip_count--;

                    // Also remove all bookings for this trip
                    int booking_removed = 0;
                    for (int j = 0; j < booking_count; j++)
                    {
                        if (bookings[j].trip_id == trip_id)
                        {
                            for (int k = j; k < booking_count - 1; k++)
                            {
                                bookings[k] = bookings[k + 1];
                            }
                            booking_count--;
                            j--; // Check the same index again as elements shifted
                            booking_removed++;
                        }
                    }

                    printf("Trip cancelled successfully! %d bookings were also cancelled.\n", booking_removed);
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                printf("Trip not found!\n");
            }
            break;
        }
        case 4:
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

// View all bookings
void view_bookings()
{
    printf("\n=== All Bookings ===\n");
    printf("ID\tTrip\tPassenger\tSeat\tFare\tBooked On\n");

    for (int i = 0; i < booking_count; i++)
    {
        char time_str[20];
        strftime(time_str, 20, "%Y-%m-%d %H:%M", localtime(&bookings[i].booking_time));

        printf("%d\t%d\t%s\t%d\t%.2f\t%s\n",
               bookings[i].id, bookings[i].trip_id,
               bookings[i].passenger_name, bookings[i].seat_number,
               bookings[i].fare_paid, time_str);
    }
}

// View available trips
void view_available_trips()
{
    printf("\n=== Available Trips ===\n");
    printf("ID\tRoute\t\tDeparture\tArrival\tAvailable Seats\n");

    for (int i = 0; i < trip_count; i++)
    {
        if (trips[i].available_seats <= 0)
            continue;

        // Get route info
        char route_info[50] = "N/A";
        for (int j = 0; j < route_count; j++)
        {
            if (routes[j].id == trips[i].route_id)
            {
                sprintf(route_info, "%s-%s", routes[j].source, routes[j].destination);
                break;
            }
        }

        printf("%d\t%s\t%s\t%s\t%d\n",
               trips[i].id, route_info,
               trips[i].departure_time, trips[i].arrival_time,
               trips[i].available_seats);
    }

    int trip_id;
    printf("\nEnter Trip ID to view details (0 to go back): ");
    scanf("%d", &trip_id);

    if (trip_id != 0)
    {
        display_trip_details(trip_id);
    }
}

// Display trip details
void display_trip_details(int trip_id)
{
    int found = 0;

    for (int i = 0; i < trip_count; i++)
    {
        if (trips[i].id == trip_id)
        {
            found = 1;

            // Get vehicle info
            char vehicle_info[30] = "N/A";
            for (int j = 0; j < vehicle_count; j++)
            {
                if (vehicles[j].id == trips[i].vehicle_id)
                {
                    sprintf(vehicle_info, "%s (%s)", vehicles[j].type, vehicles[j].registration);
                    break;
                }
            }

            // Get route info
            char route_info[50] = "N/A";
            float distance = 0;
            float fare_per_km = 0;
            for (int j = 0; j < route_count; j++)
            {
                if (routes[j].id == trips[i].route_id)
                {
                    sprintf(route_info, "%s to %s", routes[j].source, routes[j].destination);
                    distance = routes[j].distance;
                    fare_per_km = routes[j].fare_per_km;
                    break;
                }
            }

            printf("\n=== Trip Details ===\n");
            printf("Trip ID: %d\n", trips[i].id);
            printf("Vehicle: %s\n", vehicle_info);
            printf("Route: %s (%.2f km)\n", route_info, distance);
            printf("Fare Rate: %.2f per km\n", fare_per_km);
            printf("Departure: %s\n", trips[i].departure_time);
            printf("Arrival: %s\n", trips[i].arrival_time);
            printf("Available Seats: %d\n", trips[i].available_seats);

            // Calculate sample fare
            if (trips[i].available_seats > 0)
            {
                printf("Sample fare for 1 seat: %.2f\n", calculate_fare(trips[i].route_id, 1));
            }

            break;
        }
    }

    if (!found)
    {
        printf("Trip not found!\n");
    }
}

// Book ticket
void book_ticket()
{
    view_available_trips();

    int trip_id;
    printf("\nEnter Trip ID to book (0 to cancel): ");
    scanf("%d", &trip_id);

    if (trip_id == 0)
        return;

    // Find the trip
    int trip_index = -1;
    for (int i = 0; i < trip_count; i++)
    {
        if (trips[i].id == trip_id)
        {
            trip_index = i;
            break;
        }
    }

    if (trip_index == -1)
    {
        printf("Invalid Trip ID!\n");
        return;
    }

    if (trips[trip_index].available_seats <= 0)
    {
        printf("No available seats on this trip!\n");
        return;
    }

    // Get passenger details
    Booking b;
    b.id = booking_count + 1;
    b.trip_id = trip_id;

    printf("Enter Passenger Name: ");
    scanf(" %[^\n]", b.passenger_name); // Read full name with spaces

    int seat_count;
    printf("Enter Number of Seats to Book: ");
    scanf("%d", &seat_count);

    if (seat_count <= 0)
    {
        printf("Invalid seat count!\n");
        return;
    }

    if (seat_count > trips[trip_index].available_seats)
    {
        printf("Only %d seats available!\n", trips[trip_index].available_seats);
        return;
    }

    // Calculate fare
    float fare = calculate_fare(trips[trip_index].route_id, seat_count);
    printf("Total Fare: %.2f\n", fare);

    char confirm;
    printf("Confirm booking? (y/n): ");
    scanf(" %c", &confirm);

    if (tolower(confirm) != 'y')
    {
        printf("Booking cancelled.\n");
        return;
    }

    // Assign seats and create booking
    for (int i = 0; i < seat_count; i++)
    {
        int seat_num = find_available_seat(trip_id);

        Booking new_booking;
        new_booking.id = booking_count + 1;
        new_booking.trip_id = trip_id;
        strcpy(new_booking.passenger_name, b.passenger_name);
        new_booking.seat_number = seat_num;
        new_booking.booking_time = time(NULL);
        new_booking.fare_paid = fare / seat_count; // Split fare equally per seat

        bookings[booking_count++] = new_booking;
    }

    // Update available seats
    trips[trip_index].available_seats -= seat_count;

    printf("Booking successful! Your booking ID is %d\n", b.id);
    printf("Seats booked: %d\n", seat_count);
    printf("Total amount paid: %.2f\n", fare);
}

// Cancel ticket
void cancel_ticket()
{
    int booking_id;
    printf("Enter Booking ID to cancel: ");
    scanf("%d", &booking_id);

    int found = 0;
    for (int i = 0; i < booking_count; i++)
    {
        if (bookings[i].id == booking_id)
        {
            found = 1;

            // Find the trip
            for (int j = 0; j < trip_count; j++)
            {
                if (trips[j].id == bookings[i].trip_id)
                {
                    // Increase available seats
                    trips[j].available_seats++;

                    // Remove the booking
                    for (int k = i; k < booking_count - 1; k++)
                    {
                        bookings[k] = bookings[k + 1];
                    }
                    booking_count--;

                    printf("Booking cancelled successfully!\n");
                    printf("Refund amount: %.2f\n", bookings[i].fare_paid);

                    break;
                }
            }

            break;
        }
    }

    if (!found)
    {
        printf("Booking not found!\n");
    }
}

// Calculate fare
float calculate_fare(int route_id, int seat_count)
{
    for (int i = 0; i < route_count; i++)
    {
        if (routes[i].id == route_id)
        {
            return routes[i].distance * routes[i].fare_per_km * seat_count;
        }
    }
    return 0;
}

// Find available seat number
int find_available_seat(int trip_id)
{
    int max_seat = 0;

    // Find vehicle capacity
    for (int i = 0; i < trip_count; i++)
    {
        if (trips[i].id == trip_id)
        {
            for (int j = 0; j < vehicle_count; j++)
            {
                if (vehicles[j].id == trips[i].vehicle_id)
                {
                    max_seat = vehicles[j].capacity;
                    break;
                }
            }
            break;
        }
    }

    // Find all booked seats for this trip
    int booked_seats[max_seat];
    for (int i = 0; i < max_seat; i++)
    {
        booked_seats[i] = 0;
    }

    for (int i = 0; i < booking_count; i++)
    {
        if (bookings[i].trip_id == trip_id)
        {
            if (bookings[i].seat_number > 0 && bookings[i].seat_number <= max_seat)
            {
                booked_seats[bookings[i].seat_number - 1] = 1;
            }
        }
    }

    // Find first available seat
    for (int i = 0; i < max_seat; i++)
    {
        if (booked_seats[i] == 0)
        {
            return i + 1; // Seat numbers start from 1
        }
    }

    return -1; // No available seat (shouldn't happen as we check availability before)
}