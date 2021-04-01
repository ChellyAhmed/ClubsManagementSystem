#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#define max_char 100
#define max_clubs 100
#define max_users 100
#define max_activities 50
struct Activity
{
    char name[max_char];
    char description[max_char];
};
typedef struct Activity Activity;
struct Club
{
    char name[max_char];
    char field[max_char];
    char description[100];
    int president_id; //Contains the ID of the president
    int num_of_members;
    int members[100];
    int num_activities;
    bool approved;
    Activity activities[max_activities];
};
typedef struct Club Club;

struct User
{
    int id;
    char name[100];
    char email[100];
    char password[100];
    int grp;                       //0= admin 1= freshman 2= sophomore ...etc
    char president_name[max_char]; //Name of the club in which president. If name is"?"  then is not president at all
};
typedef struct User User;
int look_for_club_name(Club clubs[], int num_clubs, char name[])
{
    for (int i = 0; i < (num_clubs); i++)
    {
        if (strcmp(name, clubs[i].name) == 0)
        {
            return i;
        }
    }
}
int look_for_id(User users[], int num_users, int id_connected[])
{ //Returns index of User based on the ID. Returns -1 if id doesn't exist.
    int index = -1;
    for (int i = 0; i < num_users; i++)
    {
        if (id_connected == users[i].id)
        {
            index = i;
        }
    }
    return index;
}
int login(User users[], int num_users)
{ //Returns ID of the connected User. Returns 0 if no one is connected.
    int id_connected;
    char password[100];
    printf("Input id: ");
    fflush(stdin);
    scanf("%d", &id_connected);
    printf("Input password: ");
    fflush(stdin);
    gets(password);
    int index = look_for_id(users, num_users, id_connected);
    //Compare password.
    if (strcmp(password, users[index].password) != 0 || (index == -1))
    {
        id_connected = 0;
        printf("Please check your inputs\n");
    }
    else
    {

        printf("Welcome %s ! You are now logged in.\n", users[(index)].name);
    }
    return id_connected;
}
int trueemail(char s[])
{
    int wselt = 0;
    char domain[12];
    char stars[] = "***********";
    strcpy(domain, stars);
    int i = 1, wa9af = 0;

    while (wa9af == 0 && i <= strlen(s))
    {
        if (s[i] == '@')
        {

            for (int j = 0; j < strlen(s) - i; j++)
            {
                domain[j] = s[i + j];
            }
            wa9af = 1;
        }

        i++;
    }
    if (strcmp("@medtech.tn", domain) == 0)
    {
        return 1;
    }
    else if (strcmp("@msb.tn****", domain) == 0)
    {
        return 1;
    }
    else if (strcmp("@lci.tn****", domain) == 0)
    {
        return 1;
    }
    else if (strcmp("@smu.tn****", domain) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Uniqueid(User users[], int num_users)
{
    int occ = 1;
    if (users[num_users].id < 1)
    {
        occ = 0;
    }
    int i = 0;
    while ((occ == 1) && (i < num_users))
    {
        if (users[i].id == users[num_users].id)
        {
            occ = 0;
        }
        i++;
    }
    return occ;
}

void signup(User users[], int *num_users)
{
    printf("Input your name: ");
    fflush(stdin);
    gets(users[*num_users].name);

    do
    {
        printf("Input your email: ");
        fflush(stdin);
        gets(users[*num_users].email);
        strlwr(users[*num_users].email);
    } while (trueemail(users[*num_users].email) == 0);

    do
    {
        printf("Input your ID: ");
        fflush(stdin);
        scanf("%d", &users[*num_users].id);
    } while (Uniqueid(users, *num_users) == 0);

    printf("create your password. It is case-sensitive. (make sure no untrusty person is looking at the screen.): ");
    fflush(stdin);
    gets(users[*num_users].password);
    printf("Password saved. Please don't forget your password.\n");
    if (*num_users != 0)
    {
        do
        {
            printf("Input your group. (1=Freshman|L1\t2=Sohpohomore|L2\t3=Junior|L3\t4=Senior\t5=Final:\t");
            fflush(stdin);
            scanf("%d", &users[*num_users].grp);
        } while (((users[*num_users].grp < 1) || (users[*num_users].grp > 5)));
    }
    else
    {
        printf("Since you are the first user to sign up, you are automatically chosen as the system superadmin.\n");
        users[*num_users].grp = 0;
    }

    strcpy(users[*num_users].president_name, "?");
    printf("\aDear %s, Welcome to our system.\nYou may log in now with your password. Note that you are not enrolled in any club.\n", users[*num_users].name);

    (*num_users)++;
}
void show_users(User users[], int *num_users)
{
    printf("Showing users\n");
    for (int i = 0; i < (*num_users); i++)
    {
        printf("User number %d\n", (i + 1));
        printf("\tName: %s \n", users[i].name);
        printf("\tEmail: %s\n", users[i].email);
        printf("\tid: %d \n", users[i].id);
        if (users[i].grp == 0)
        {
            printf("\tThis user is an admin.\n");
        }
        else
        {
            printf("\tUser is in his academic year number: %d \n", users[i].grp);
        }
        if (strcmp(users[i].president_name, "?") == 0)
        {
            printf("\tThis user is not the president of any club.\n");
        }
        else
        {
            printf("\tThis user is the president of the club: %s\n", users[i].president_name);
        }
    }
}

void update_details(Club clubs[], int num, User users[], int num_users, char name_of_club[])
{
    //printf("\n***UPDATE DETAILS***\n");
    //name_of_club contains the name of the club to update
    int president_id;
    int new_president;
    int old;
    int choice;
    for (int i = 0; i < max_clubs; i++)
    {
        if (strcmp(name_of_club, clubs[i].name) == 0)
        {
            printf("1- change name\n");
            printf("2- change field\n");
            printf("3- change description\n");
            printf("4- change president\n");
            printf("5- change Activity\n");
            printf("\n");
            fflush(stdin);
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                printf("enter new name of club : ");
                fflush(stdin);
                gets(clubs[i].name);
                //Update name in user
                president_id = look_for_id(users, num_users, clubs[i].president_id);
                strcpy(users[president_id].president_name, clubs[i].name);
                break;
            case 2:
                printf("enter new field : ");
                fflush(stdin);
                scanf("%s", &clubs[i].field);
                break;
            case 3:
                printf("enter new description : ");
                fflush(stdin);
                scanf("%s", &clubs[i].description);
                break;
            case 4:
                printf("If you are the president of this club, you will assign a new president.\nenter ID of new president : ");
                fflush(stdin);
                scanf("%d", &new_president);
                president_id = look_for_id(users, num_users, new_president);
                if (president_id == -1)
                {
                    printf("Check inputs\n");
                }
                else
                {
                    old = look_for_id(users, num_users, clubs[i].president_id);
                    strcpy(users[old].president_name, "?");
                    clubs[i].president_id = new_president;
                    strcpy(users[president_id].president_name, clubs[i].name);
                }
                break;
            case 5:
                manage_activities(clubs[i].activities, &clubs[i].num_activities);
                break;
            }
        }
    }
    printf("\n\n");
}

void remove_user(User users[], int *num_users, Club clubs[], int *num_clubs, int poorman) //poorman contains the ID of the user to delete
{

    int poor_index = look_for_id(users, *num_users, poorman);
    if (poor_index == -1)
    {
        printf("No user has been found with the ID you typed. We recommend executing the \"Show Users\"function\n");
    }
    else if (users[poor_index].grp == 0)
    {
        printf("This user is an admin! Can't remove admin.\n\a");
    }
    else if (strcmp(users[poor_index].president_name, "?") != 0)
    {
        printf("This user is the president of %s! Please update club president before removing him.\n\a", users[poor_index].president_name);
    }
    else
    {
        for (int i = poor_index; i < (*num_users); i++)
        {
            users[i] = users[i + 1];
        }
        (*num_users)--;
        printf("User successfully removed!");
    }
    for (int i = 0; i < (*num_clubs); i++)
    {
        for (int j = 0; j < (clubs[i].num_of_members); j++)
        {
            if (clubs[i].members[j] == poorman)
            {
                clubs[i].members[j] = 0;

                for (int k = j; k < (clubs[i].num_of_members - 1); k++)
                {
                    clubs[i].members[k] = clubs[i].members[k + 1];
                }
                clubs[i].num_of_members--;
            }
        }
    }
}
void show_clubs(Club clubs[], int *num)
{
    printf("\n***CLUBS LIST***\n");
    for (int i = 0; i < (*num); i++)
    {
        printf("%d- %s\n", i, clubs[i].name);
        printf("\tClub field %s\n", clubs[i].field);
        printf("\tClub description: %s\n", clubs[i].description);
        printf("\tClub president ID %d\n", clubs[i].president_id);
        printf("\tClub members:\n");

        for (int j = 0; j < clubs[i].num_of_members; j++)
        {
            printf("\t\tMember %d id: %d\n", j, clubs[i].members[j]);
        }
    }
}
void approve_club(Club clubs[], int num_clubs)
{
    int choice_approval;
    for (int i = 0; i < num_clubs; i++)
    {
        printf("If there are not approved clubs, they will be shown below:\n");
        if (clubs[i].approved == false)
        {
            printf("Club %s is not approved, press 1 to approve, press any button else to keep approval pending\n", clubs[i].name);
            fflush(stdin);
            scanf("%d", &choice_approval);
            if (choice_approval == 1)
            {
                clubs[i].approved = true;
                printf("club %s is approved!", clubs[i].name);
            }
        }
    }
}
void menu_admin(User users[], int *num_users, Club clubs[], int *num_clubs, int index_user, int *id_connected)
{
    int choice;
    char name_of_club[max_char];
    printf("\n***ADMIN***\n");
    printf("1- Show list of users\n");
    printf("2- remove user\n");
    printf("3- Show details of all club\n");
    printf("4- update club details\n");
    printf("5- Remove a club\n");
    printf("6- Approve non approved clubs\n");
    char name_to_remove[max_char];
    int ex_president_id;
    printf("0- Log out\n");
    printf("select your choice : \n");
    fflush(stdin);
    scanf("%d", &choice);
    printf("\n");
    int choice_tests;
    int poorman;
    switch (choice)
    {
    case 1:
        show_users(users, num_users);
        break;

    case 2:
        fflush(stdin);
        printf("Input the ID of the user you would like to remove: ");
        fflush(stdin);
        scanf("%d", &poorman);
        remove_user(users, num_users, clubs, num_clubs, poorman);
        break;

    case 3:
        show_clubs(clubs, num_clubs);
        break;
    case 4:
        printf("Enter club name to update: ");
        fflush(stdin);
        gets(name_of_club);
        update_details(clubs, (*num_clubs), users, (*num_users), name_of_club);
        break;
    case 5:
        printf("enter the name of the club you want to remove : ");
        fflush(stdin);
        scanf("%s", &name_to_remove);
        ex_president_id = remove_club(clubs, num_clubs, users[index_user].president_name);
        ex_president_id = look_for_id(users, (*num_users), ex_president_id);
        strcpy(users[ex_president_id].president_name, "?");
        break;
    case 6:
        approve_club(clubs, (*num_clubs));
        break;
    case 0:
        (*id_connected) = 0;
        break;
    }
}
int remove_club(Club *clubs, int *num, char name_of_club[max_char])
{
    printf("\n***REMOVE CLUB***\n");
    int president_id;
    int cons;
    for (int i = 0; i < *num; i++)
    {
        if (strcmp(name_of_club, clubs[i].name) == 0)
        {
            cons = i;
        }
    }
    president_id = clubs[cons].president_id;
    for (int j = cons; j < *num; j++)
    {
        clubs[j] = clubs[j + 1];
    }
    (*num)--;

    printf("the club has been removed.");
    printf("\n\n");
    return president_id;
}
void add_Activity(Activity activities[], int *num)
{
    printf("enter the name of Activity: ");
    fflush(stdin);
    scanf("%s", activities[*num].name);
    printf("enter the description of the Activity : ");
    fflush(stdin);
    scanf("%s", &activities[*num].description);
    *num = *num + 1;
}
void remove_activity(Activity activities[], int *num)
{
    printf("\n***REMOVE ACTIVITIES***\n");
    int index;
    printf("enter the index of Activity you want to remove : ");
    fflush(stdin);
    scanf("%d", &index);
    if (index >= 0 && index < (*num))
    {
        for (int j = index; j < *num; j++)
        {
            activities[j] = activities[j + 1];
        }
        (*num)--;
        printf("the Activity has been removed.");
        printf("\n\n");
    }
    else
    {
        printf("Please check the index.");
    }
}
void show_list(Activity activities[], int num)
{
    printf("\n***SHOW LIST***\n");
    for (int i = 0; i < num; i++)
    {
        printf("\t%d- %s \n", i, activities[i].name);
        printf("description : %s\n", activities[i].description);
    }
}
void manage_activities(Activity activities[], int *num)
{
    int choice;
    do
    {
        printf("\n***ACTIVITIES MANAGEMENT***\n");
        printf("1- add Activity\n");
        printf("2- remove Activity\n");
        printf("3- show list\n");
        fflush(stdin);
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
        case 1:
            add_Activity(activities, num);
            break;

        case 2:
            remove_activity(activities, num);
            break;

        case 3:
            show_list(activities, *num);
            break;
        }
    } while ((choice != 1) && (choice != 2) && (choice != 3));
}
void mcq(Club clubs[], int num_clubs)
{
    int choice_mcq;
    char recoclubs[100][100];
    int num_rec_clubs = 0;
    for (int i = 0; i < num_clubs; i++)
    {
        printf("Do you like %s\n", clubs[i].field);
        do
        {
            printf("1: YES ||2: No|| Input choice: ");
            fflush(stdin);
            scanf("%d", &choice_mcq);
        } while (choice_mcq != 1 && choice_mcq != 2);
        if (choice_mcq == 1)
        {
            strcpy(recoclubs[num_rec_clubs], clubs[i].name);
            num_rec_clubs++;
        }
    }
    printf("Do you want to join the clubs of your friends?");
    do
    {
        printf("1: YES ||2: No|| Input choice: ");
        fflush(stdin);
        scanf("%d", &choice_mcq);
    } while (choice_mcq != 1 && choice_mcq != 2);
    int numfriends;
    if (choice_mcq == 1)
    {
        printf("Input the number of your friends: ");
        fflush(stdin);
        scanf("%d", &numfriends);
        int frend_id;
        bool mawjoud;
        for (int i = 0; i < numfriends; i++)
        {
            printf("Input the ID of your friend number %d: ", i + 1);
            fflush(stdin);
            scanf("%d", &frend_id);
            for (int j = 0; j < num_clubs; j++)
            {
                for (int k = 0; k < clubs[j].num_of_members; k++)
                {
                    if (frend_id == clubs[j].members[k])
                    {
                        mawjoud = false;
                        for (int l = 0; l < num_rec_clubs; l++)
                        {
                            if (strcmp(recoclubs[l], clubs[j].name) == 0)
                            {
                                mawjoud = true;
                            }
                        }
                        if (mawjoud = false)
                        {
                            strcpy(recoclubs[num_rec_clubs], clubs[j].name);
                            num_rec_clubs++;
                        }
                    }
                }
            }
        }
    }
    if (num_rec_clubs > 0)
    {
        printf("We recommend the following clubs:\n");
        for (int i = 0; i < num_rec_clubs; i++)
        {
            printf("%s\n", recoclubs[i]);
        }
    }
    else
    {
        printf("We couldn't recommend any club, please choose from list.\n");
    }
}
void member_list(Club clubs[], int num_clubs, char clubName[])
{
    int index;
    index = look_for_club_name(clubs, num_clubs, clubName);
    int num_of_members = clubs[index].num_of_members;
    if (clubs[index].num_of_members == 0)
    {
        printf("There are currently no members in this club\n");
    }
    else
    {
        for (int i = 0 ; i< num_of_members ; i++)
        {
            printf("member %d has the following id: %d\n",i,clubs[index].members[i]);
        }
    }
}
remove_member(Club clubs[], int num_clubs, char clubName[])
{
    int index;
    index = look_for_club_name(clubs, num_clubs, clubName);
    int poorMember;
    do
    {
        printf("Input the index of the user you want to remove: ");
        fflush(stdin);
        scanf("%d", &poorMember);
    } while (poorMember < 0 || poorMember > clubs[index].num_of_members);
    if (clubs[index].members[poorMember] == clubs[index].president_id)
    {
        printf("This member is you. Can not remove it\n");
    }
    else
    {
        for (int j = poorMember; j < (clubs[index].num_of_members - 1); j++)
        {
            clubs[index].members[j] = clubs[index].members[j + 1];
        }
        printf("Member removed\n");
        clubs[index].num_of_members--;
    }
}
void menu_president(Club clubs[], int *num_clubs, User users[], int *num_users, int index_user, int *id_connected)
{
    int choice;

    printf("\n***president***\n");
    printf("1- join club\n");
    int club_to_join;
    int choice_join;
    printf("2- Show details of all clubs\n");
    printf("3- remove the club in which you're president\n");
    char name_to_remove[max_char];
    printf("4- update club details (Only club in which you're the president)\n");
    printf("5- Manage activities\n");
    int club_index;
    printf("6- members list\n");
    printf("7- remove members\n");
    printf("8- delete my account\n");
    printf("0- Log out\n");
    printf("select your choice : \n");
    fflush(stdin);
    scanf("%d", &choice);
    printf("\n");
    switch (choice)
    {
    case 1:
        do
        {
            printf("1- Select from list\n");
            printf("2- See the clubs we recommend\n");
            printf("3- Back to menu\n");
            printf("Input choice: ");
            fflush(stdin);
            scanf("%d", &choice_join);
        } while (choice_join != 1 && choice_join != 2 && choice_join != 3);
        if (choice_join == 1)
        {
            show_clubs(clubs, num_clubs);
            do
            {
                printf("Input club index: ");
                fflush(stdin);
                scanf("%d", &club_to_join);
            } while (club_to_join < 0 || club_to_join > (*num_clubs));
            clubs[club_to_join].members[clubs[club_to_join].num_of_members] = (*id_connected);
            clubs[club_to_join].num_of_members++;
            printf("You are added as one member in the club");
        }
        else if (choice_join == 2)
        {
            mcq(clubs, (*num_clubs));
        }
        break;
    case 2:
        show_clubs(clubs, num_clubs);
        break;
    case 3:
        remove_club(clubs, num_clubs, users[index_user].president_name);
        strcpy(users[index_user].president_name, "?");
        break;
    case 4:
        update_details(clubs, (*num_clubs), users, (*num_users), users[index_user].president_name);
        break;
    case 5:
        for (int i = 0; i < (*num_clubs); i++)
        {
            if (strcmp(users[index_user].president_name, clubs[i].name) == 0)
            {
                club_index = i;
            }
        }
        manage_activities(clubs[club_index].activities, &clubs[club_index].num_activities);
        break;
    case 6:
        member_list(clubs, (*num_clubs), users[index_user].president_name);
        break;
    case 7:
        remove_member(clubs, (*num_clubs), users[index_user].president_name);
        break;
    case 8:
        printf("You are currently the president of the club: %s\nYou can only delete your account if you choose another president", users[index_user].president_name);
        break;
    case 0:
        (*id_connected) = 0;
        break;
    }
}
void add_club(Club clubs[], int *num, int id_connected)
{
    printf("\n***ADD CLUB***\n");
    int repeated_club_name = 0;
    do
    {
        printf("name of club : ");
        fflush(stdin);
        scanf("%s", &clubs[*num].name);
        repeated_club_name = 0;
        for (int i = 0; i < *num; i++)
        {
            if (strcmp(clubs[i].name, clubs[*num].name) == 0)
            {
                repeated_club_name++;
            }
        }
    } while (repeated_club_name != 0);
    printf("field of the club : ");
    fflush(stdin);
    scanf("%s", &clubs[*num].field);
    printf("description : ");
    clubs[(*num)].num_activities = 0;
    fflush(stdin);
    scanf("%s", &clubs[*num].description);
    clubs[(*num)].president_id = (id_connected);

    clubs[(*num)].members[clubs[(*num)].num_of_members] = id_connected;
    clubs[(*num)].num_of_members = 1;
    clubs[(*num)].approved = false;

    *num = *num + 1;
    printf("\n\n");
}
Resgin(Club clubs[], int num_clubs, int id_connected)
{
    int choice;
    bool remove = false;
    for (int i = 0; i < num_clubs; i++)
    {
        remove = false;
        for (int j = 0; j < clubs[i].num_of_members; j++)
        {
            if (clubs[i].members[j] == id_connected && (remove == false))
            {
                printf("Do you want to resign from %s\n", clubs[i].name);
                do
                {
                    printf("1: Yes || 2: No: => ");
                    fflush(stdin);
                    scanf("%d", &choice);
                } while (choice != 1 && choice != 2);
                if (choice == 1)
                {
                    remove = true;
                    clubs[i].num_of_members--;
                }
            }
            if (remove)
            {
                clubs[i].members[j] = clubs[i].members[j + 1];
            }
        }
    }
}
void menu_user(User users[], int *num_users, Club clubs[], int *num_clubs, int *id_connected)
{
    int choice, user_index;

    printf("\n***USER***\n");
    printf("1- join club\n");
    int club_to_join;
    int choice_join;
    printf("2- Show details of all clubs\n");
    printf("3- create a club\n");
    printf("4- resign from club\n");
    printf("5- delete my account\n");
    printf("0- Log out\n");
    printf("select your choice : \n");
    fflush(stdin);
    scanf("%d", &choice);
    printf("\n");
    switch (choice)
    {
    case 1:
        //join_club();
        do
        {
            printf("1- Select from list\n");
            printf("2- See the clubs we recommend\n");
            printf("3- Back to menu\n");
            printf("Input choice: ");
            fflush(stdin);
            scanf("%d", &choice_join);
        } while (choice_join != 1 && choice_join != 2 && choice_join != 3);
        if (choice_join == 1)
        {
            show_clubs(clubs, num_clubs);
            do
            {
                printf("Input club index: ");
                fflush(stdin);
                scanf("%d", &club_to_join);
            } while (club_to_join < 0 || club_to_join > (*num_clubs));
            clubs[club_to_join].members[clubs[club_to_join].num_of_members] = (*id_connected);
            clubs[club_to_join].num_of_members++;
            printf("You are added as one member in the club");
        }
        else if (choice_join == 2)
        {
            mcq(clubs, (*num_clubs));
        }
        break;
        break;

    case 2:
        show_clubs(clubs, num_clubs);
        break;

    case 3:
        user_index = look_for_id(users, (*num_users), (*id_connected));
        add_club(clubs, num_clubs, (*id_connected));
        strcpy(users[user_index].president_name, clubs[(*num_clubs) - 1].name);
        break;
    case 4:
        Resgin(clubs, (*num_clubs), (*id_connected));
        break;
    case 5:
        remove_user(users, num_users, clubs, num_clubs, (*id_connected));
        (*id_connected) = 0;
        break;
    case 0:
        (*id_connected) = 0;
        break;
    }
}
void main()
{

    int num_users = 0;
    FILE *file_num_users;
    file_num_users = fopen("numusers.txt", "r");
    fscanf(file_num_users, "%d", &num_users);
    int num_clubs = 0;
    FILE *file_num_clubs;
    file_num_clubs = fopen("numclubs.txt", "r");
    fscanf(file_num_clubs, "%d", &num_clubs);
    User users[max_users];
    FILE *file_users;
    file_users = fopen("users.bin", "rb");

    for (int i = 0; i < num_users; i++)
    {
        fread(&users[i], sizeof(User), 1, file_users);
    }

    Club clubs[max_clubs];
    FILE *file_clubs;
    file_clubs = fopen("clubs.bin", "rb");
    for (int i = 0; i < num_clubs; i++)
    {
        fread(&clubs[i], sizeof(Club), 1, file_clubs);
    }
    int id_connected = 0; // the ID of the current connected user. 0 means no one is connected.
    char ans[100];
    printf("Welcome to the clubs management system.\n");
    bool quit = false;
    while (!quit)
    {

        if (id_connected == 0)
        {
            do
            {
                printf("1- Log in\n2- Sign up\n0- Quit\n");
                fflush(stdin);
                gets(ans);
            } while ((strcmp(ans, "1") != 0) && (strcmp(ans, "2") != 0) && (strcmp(ans, "0") != 0));
            switch (atoi(ans))
            {
            case 1:
                system("cls");                          //Clears console.
                id_connected = login(users, num_users); // LOG IN FUCTION. returns 0 if false inputs. Else, it returns the ID of the connected user.
                break;
            case 2:
                system("cls");             //Clears console.
                signup(users, &num_users); //SIGN UP FUNCTION (Register // Create an account)
                break;
            case 0:
                printf("Thank you for using our system!");
                quit = true;
                break;
            }
        }
        else
        {
            int index_user = look_for_id(users, num_users, id_connected);

            if (index_user == 0)
            {
                menu_admin(users, &num_users, &clubs, &num_clubs, index_user, &id_connected);
            }
            else if (strcmp(users[index_user].president_name, "?") != 0)
            {
                menu_president(clubs, &num_clubs, users, &num_users, index_user, &id_connected);
            }
            else
            {
                menu_user(users, &num_users, clubs, &num_clubs, &id_connected);
            }
        }
    }
    fclose(file_clubs);
    fclose(file_num_clubs);
    fclose(file_num_users);
    fclose(file_users);
    file_num_users = fopen("numusers.txt", "w");
    fprintf(file_num_users, "%d", num_users);
    file_num_clubs = fopen("numclubs.txt", "w");
    fprintf(file_num_clubs, "%d", num_clubs);
    file_users = fopen("users.bin", "wb");
    for (int i = 0; i < num_users; i++)
    {
        fwrite(&users[i], sizeof(User), 1, file_users);
    }
    file_clubs = fopen("clubs.bin", "wb");
    for (int i = 0; i < num_clubs; i++)
    {
        fwrite(&clubs[i], sizeof(Club), 1, file_clubs);
    }
}
