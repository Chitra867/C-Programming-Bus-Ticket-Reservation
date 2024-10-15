#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure to hold ticket information
struct ticket {
    char name[50];
    char address_from[100];
    char address_to[100];
    char seatnum[10];
    char date[50];
    double contact_Number;
};

// Function declarations
void signup();
void login();
void Seat_Booking();
void Check_Seat();
void Cancel_Seat();
void Search_Seat();
void Update_Seat();

int main() {
    int choice;
    // Main menu loop
    while (1) {
        printf("\nWelcome to the bus reservation system\n");
        printf("\t1. Sign up\n");
        printf("\t2. Login\n");
        printf("\t3. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                signup(); // Call signup function
                break;
            case 2:
                login(); // Call login function
                
                // After successful login, show another menu for seat-related operations
                do {
                    printf("\nPress 1 for Booking Seat.\n");
                    printf("Press 2 for Check Seat.\n");
                    printf("Press 3 for Cancel Seat.\n");
                    printf("Press 4 for Search Seat.\n");
                    printf("Press 5 for Update Seat.\n");
                    printf("Press 6 to Log Out.\n");
                    printf("\nEnter your choice: ");
                    scanf("%d", &choice);
                    
                    switch (choice) {
                        case 1:
                            system("cls"); // Clear screen
                            Seat_Booking(); // Call function to book a seat
                            break;
                        case 2:
                            system("cls");
                            Check_Seat(); // Call function to check seat
                            break;
                        case 3:
                            system("cls");
                            Cancel_Seat(); // Call function to cancel seat
                            break;
                        case 4:
                            system("cls");
                            Search_Seat(); // Call function to search seat
                            break;
                        case 5:
                            system("cls");
                            Update_Seat(); // Call function to update seat
                            break;
                        case 6:
                            system("cls");
                            printf("Logged out.\n");
                            break;
                        default:
                            printf("\nYou entered the wrong number! Please enter a correct number.\n");
                            break;
                    }
                    if (choice == 6) break;
                    
                    char c;
                    printf("\nGo to menu press 'G' else any letter to log out: ");
                    while ((getchar()) != '\n'); // Clear the input buffer
                    scanf("%c", &c);
                    
                    if (c != 'g' && c != 'G') break;
                } while (1);
                
                printf("Thanks for using our Bus Service.\n");
                break;
            case 3:
                printf("Exiting program...\n");
                exit(0); // Exit program
            default:
                printf("Invalid choice.\n");
        }
    }
}

// Function to sign up new users
void signup() {
    char username[20], password[20];
    FILE *fp;
    
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    
    fp = fopen("users.txt", "w"); // Open file to save username and password
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        exit(1);
    }
    
    fprintf(fp, "%s %s\n", username, password); // Write username and password to file
    fclose(fp);
    
    printf("Account created successfully.\n");
}

// Function for user login
void login() {
    char username[20], password[20], file_username[20], file_password[20];
    FILE *fp;
    
    do {
        fp = fopen("users.txt", "r"); // Open file to read username and password
        if (fp == NULL) {
            printf("Error: Unable to open file.\n");
            exit(1);
        }
        
        printf("\nEnter username: ");
        scanf("%s", username);
        printf("\nEnter password: ");
        scanf("%s", password);
        
        fscanf(fp, "%s %s", file_username, file_password); // Read username and password from file
        
        // Check if the entered credentials match the stored ones
        if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0) {
            printf("\nLogin successful.\n\n");
            fclose(fp);
            return;
        } else {
            printf("Incorrect username or password.\n\n");
            fclose(fp);
        }
    } while (1);
}

// Function to book a seat
void Seat_Booking() {
    struct ticket s;
    FILE *fpr;
    
    fpr = fopen("Booking_Store.txt", "ab"); // Open file in append mode
    if (fpr == NULL) {
        printf("Error: Unable to open booking file.\n");
        return;
    }
    
    char seats[][4] = {"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "A10", 
                       "A11", "A12", "A13", "A14", "B1", "B2", "B3", "B4", "B5", 
                       "B6", "B7", "B8", "B9", "B10", "B11", "B12", "B13", "B14", 
                       "C1", "C2", "C3", "C4", "C5", "D1", "D2"};
    
    int seat_found = 0;
    printf("\t----------------------Seat Design--------------------------\n\n");
    printf("\tD1\tD2\t\tDriver seat\n");
    printf("\t==============\n");
    printf("\tDoor\t\n");
    printf("\t==============\n");
    printf("\tLeft side seat\t\tRight side seat\n");
    
    for (int i = 0; i < 34; i += 2) {
        printf("\t%s\t%s\t\t%s\t%s\n", seats[i], seats[i+1], seats[i+14], seats[i+15]);
        if (i == 10) printf("\n");
    }
    
    printf("Enter Your Name: ");
    fflush(stdin);
    gets(s.name);
    
    printf("Enter Destination From: ");
    fflush(stdin);
    gets(s.address_from);
    
    printf("Enter Destination To: ");
    fflush(stdin);
    gets(s.address_to);
    
    printf("Enter Your contact number: ");
    scanf("%lf", &s.contact_Number);
    
    printf("Travelling Date 'yyyy-mm-dd': ");
    fflush(stdin);
    gets(s.date);
    
    printf("Choose your seat number: ");
    fflush(stdin);
    gets(s.seatnum);
    
    // Check if seat is valid
    for (int i = 0; i < 34; i++) {
        if (strcmp(seats[i], s.seatnum) == 0) {
            printf("Your seat is booked.\n");
            fwrite(&s, sizeof(struct ticket), 1, fpr); // Save ticket
            seat_found = 1;
            break;
        }
    }
    
    if (!seat_found) {
        printf("Invalid seat number. Your seat is not booked.\n");
    }
    
    fclose(fpr);
}

// Function to check the list of all booked seats
void Check_Seat() {
    FILE *fpr;
    fpr = fopen("Booking_Store.txt", "rb"); // Open file to read booking information
    if (fpr == NULL) {
        printf("Error: Unable to open booking file.\n");
        return;
    }
    
    struct ticket s;
    printf("\n\t\t\tBooking-List\n");
    printf("\nName\tFrom\tTo\tContact_Number\tDate\tSeat_Number\n");
    
    // Display all booked seats
    while (fread(&s, sizeof(struct ticket), 1, fpr)) {
        printf("\n%s\t%s\t%s\t%.0lf\t%s\t%s\n", s.name, s.address_from, s.address_to, s.contact_Number, s.date, s.seatnum);
    }
    printf("\n");
    
    fclose(fpr); // Close the file
}

// Function to cancel a booked seat
void Cancel_Seat() {
    FILE *fpr, *fptr;
    fpr = fopen("Booking_Store.txt", "rb"); // Open file to read booking information
    if (fpr == NULL) {
        printf("Error: Unable to open booking file.\n");
        return;
    }
    
    fptr = fopen("TempStore.txt", "wb"); // Open a temporary file to store updated information
    if (fptr == NULL) {
        printf("Error: Unable to open temporary file.\n");
        fclose(fpr);
        return;
    }
    
    struct ticket s;
    char Check_Name[50];
    printf("Enter Your Name: ");
    fflush(stdin);
    gets(Check_Name);
    
    // Copy all records except the one to be deleted
    int found = 0;
    while (fread(&s, sizeof(struct ticket), 1, fpr)) {
        if (strcmp(Check_Name, s.name) != 0) {
            fwrite(&s, sizeof(struct ticket), 1, fptr);
        } else {
            found = 1;
        }
    }
    
    if (!found) {
        printf("Ticket with this name not found.\n");
    } else {
        printf("Your seat is cancelled.\n");
    }
    
    fclose(fpr);
    fclose(fptr);
    
    // Replace old file with updated information
    remove("Booking_Store.txt");
    rename("TempStore.txt", "Booking_Store.txt");
}

// Function to search for a seat by name
void Search_Seat() {
    FILE *fpr;
    fpr = fopen("Booking_Store.txt", "rb"); // Open file to read booking information
    if (fpr == NULL) {
        printf("Error: Unable to open booking file.\n");
        return;
    }
    
    struct ticket s;
    char search_Name[50];
    printf("Enter your name: ");
    fflush(stdin);
    gets(search_Name);
    
    // Search for a seat by name
    int found = 0;
    while (fread(&s, sizeof(struct ticket), 1, fpr)) {
        if (strcmp(search_Name, s.name) == 0) {
            printf("\nName: %s\nFrom: %s\nTo: %s\nContact: %.0lf\nDate: %s\nSeat: %s\n", s.name, s.address_from, s.address_to, s.contact_Number, s.date, s.seatnum);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("No seat found for this name.\n");
    }
    
    fclose(fpr); // Close file
}

// Function to update seat booking information
void Update_Seat() {
    FILE *fpr, *fptr;
    fpr = fopen("Booking_Store.txt", "rb"); // Open file to read booking information
    if (fpr == NULL) {
        printf("Error: Unable to open booking file.\n");
        return;
    }
    
    fptr = fopen("TempStore.txt", "wb"); // Open a temporary file to store updated information
    if (fptr == NULL) {
        printf("Error: Unable to open temporary file.\n");
        fclose(fpr);
        return;
    }
    
    struct ticket s;
    char search_Name[50];
    printf("Enter your name: ");
    fflush(stdin);
    gets(search_Name);
    
    // Search for a record to update
    int found = 0;
    while (fread(&s, sizeof(struct ticket), 1, fpr)) {
        if (strcmp(search_Name, s.name) == 0) {
            printf("\nEnter new details\n");
            
            printf("Enter new destination From: ");
            fflush(stdin);
            gets(s.address_from);
            
            printf("Enter new destination To: ");
            fflush(stdin);
            gets(s.address_to);
            
            printf("Enter new contact number: ");
            scanf("%lf", &s.contact_Number);
            
            printf("Enter new date 'yyyy-mm-dd': ");
            fflush(stdin);
            gets(s.date);
            
            printf("Enter new seat number: ");
            fflush(stdin);
            gets(s.seatnum);
            
            found = 1;
        }
        
        fwrite(&s, sizeof(struct ticket), 1, fptr); // Write updated or original record
    }
    
    if (!found) {
        printf("No record found for this name.\n");
    } else {
        printf("Record updated successfully.\n");
    }
    
    fclose(fpr);
    fclose(fptr);
    
    // Replace old file with updated information
    remove("Booking_Store.txt");
    rename("TempStore.txt", "Booking_Store.txt");
}

