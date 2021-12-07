#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#define EXECUTION_COMMAND 200
#define MAX_LINE 128
#define MAX_COMMAND 64
#define MAX_PNAME 50
#define MAX_FILE_NAME_LENGTH 1028

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <math.h>
#include <ctype.h>

#define MAX_USERNAME 15
#define MAX_PASSWORD 25
#define MAX_USERS 10
#define accountFile "users.txt"


struct PCB
{
    char p_name[MAX_PNAME];
    char p_data[MAX_LINE];//Holds path and offset
    int offset;
    int p_class; //0 = application, 1 = system
    int p_priority; // 0-9
    int p_state; //0 = running, 1 = ready, 2 = blocked
    int isSuspended; // 0 = not suspended, 1 = suspended
    struct PCB* next;
};

typedef struct
{
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int isAdmin; // boolean. Only the root user can change this for users
    int isRoot; // boolean. Only one user will have this = 1
    int lineNumber;//Contains what line user is found in file
} User;

int numberofaccounts;
User* userList; // Should we make this global?

void printWelcome();
void printHelpMenu();
void showFunctionHelp(char* arguments);
void showVersion();
void displayTime(char* arguments);
void commandHandler(User user, User* userList, int numberofaccounts);
void red();
void blue();
void green();
void reset();
void changeDate(char* arguments);
void displayDate(char* arguments);
struct PCB* allocatePCB();
int freePCB(struct PCB* process);
struct PCB* setupPCB(char* name, int class, int priority);
void enqueue(struct PCB** head, struct PCB** pcb);
void enqueuePriority(struct PCB** head, struct PCB** PCB);
struct PCB* dequeue(struct PCB** head);
//From Ppcb.c
void suspend(char arguments[MAX_COMMAND], struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendReadyHead, struct PCB* suspendBlockHead);
void resume(char arguments[MAX_COMMAND], struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendedReadyHead, struct PCB* suspendedBlockHead);
void setPriority(char name[MAX_COMMAND], char priority[MAX_COMMAND], struct PCB* readyQueue, struct PCB* blockQueue, struct PCB* readySuspend, struct PCB* blockSuspend);
void showPCB(char name[MAX_COMMAND], struct PCB* readyQueue, struct PCB* blockQueue, struct PCB* readySuspend, struct PCB* blockSuspend);
void showQueuePCB(struct PCB* head);
void showAllPCB(struct PCB* readyHead, struct PCB* blockHead);
void createPCB(char arguments[], char argument2[], char argument3[], char argument4[], struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendedReadyHead, struct PCB* suspendedBlockHead);
void deletePCB(char name[], struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendedReadyHead, struct PCB* suspendedBlockHead);
void blockPCB(char name[], struct PCB* readyQueue, struct PCB* readySuspend, struct PCB* blockQueue, struct PCB* blockSuspend);
void unblockPCB(char name[], struct PCB* readyQueue, struct PCB* readySuspend, struct PCB* blockQueue, struct PCB* blockSuspend);
struct PCB* allocatePCB();
int freePCB(struct PCB* process);
struct PCB* setupPCB(char* name, int class, int priority);
struct PCB* findPcb(char pName[MAX_PNAME], struct PCB* readyHead, struct PCB* blockHead);
void insertPcb(struct PCB* toIn, struct PCB* readyHead, struct PCB* blockHead);
int removePcb(struct PCB* toPull, struct PCB* head);
void dispatch(struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendedReadyHead, struct PCB* suspendedBlockHead);
void interupt_handler(int interupt_val, struct PCB* process,  struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendReadyHead, struct PCB* suspendBlockHead);
void reintegrater( struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendReadyHead, struct PCB* suspendBlockHead);
//int removePcbBlocked(struct PCB* toPull, struct PCB* blockHead, struct PCB* susBlockHead);
//From files.c
void createDirectory(char folderName[]);
void viewDirectory(char directoryName[]);
void changeDirectory(char argument[]);
void deleteDirectory(char folderName[]);
void createFile(char fileName[]);
void removeFile(char fileName[]);
//from accounts.c
User initializeUser(char username[], char password[]);
int checkUserExists(User* database, char username[]);
int checkValidName(User* database, char username[]);
int checkUserAdmin(User* database, char username[]);
int checkUserRoot(User* database, char username[]);
int checkPassword(User user, char password[]);
void login(User* database, int accountNum);
void makeRoot(User user);
void makeAdmin(User* database, User root);
void removeAdmin(User* database, User root);
int validate_password(char pwd[]);
int verify_pass_len(char pwd[]);
int verify_char_rules(char pwd[]);
int verify_int_rule(char pwd[]);
int verify_specialChar_rule(char pwd[]);
int load_all_accounts(char* fileName);
User load_active_account(int line_number, char* filename);
void accounts2file(int numOfAccounts, char *filename);
void changePassword(User* database, User user);
//from admincomm.c
void addNewUser(int numUsers, char *fileLocation);
int deleteUser(User *allUsers, int numUsers, char *fileLocation, int callerIsRoot);
#endif

