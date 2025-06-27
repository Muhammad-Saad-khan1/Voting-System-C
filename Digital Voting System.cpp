#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>


//function Related to Voter
void Voter_Panel();
void SignUp();
void Login();
void DisplayElectoralSystem();
void CastVote();

//Functions Related to Admin
void Admin_Panel();
void Admin_SignUp();
void Admin_Login();
void AddCandidate();
void DisplayResults();
void DeleteCandidate();
void UpdateCandidate();

//Functions Related to Data and Design
void Load_Data();
void Save_Data();
void Star();
void waiting();

//structure for Admin Information
struct admin {
	char Admin_Name[20];
	char Admin_Password[20];
} admin_info;

int AdminCount = 0;

//structure for candidate
struct candidate {
	char C_Name[50];
	char C_Party[30];
	int vote;
} candidates[4];

int CandidateCount = 0;

//Structure for Voter Information
struct voter {
	char V_name[100];
	char V_address[100];
	char V_Mobile_number[20];
	int age;
	char V_CNIC[20];
	int IsVoted;

} voters[2000];

int VoterCount = 0;
int currentVoterIndex = -1;
FILE *DVS;

int main() {
	system("color F1");
	Load_Data();
	int choice=0;

	do {
		printf("\n\t\t\t\t\t---- Digital Voting System ----\n\n");
		printf("1:	Voter Panel\n");
		printf("2:	Admin Panel\n");
		printf("3:	Exit\n");

		printf("\n\t\t|| Choice: ");
		scanf("%d",&choice);

		switch(choice) {
			case 1:
				waiting();
				Star();
				Voter_Panel();
				break;
			case 2:
				waiting();
				Star();
				Admin_Panel();
				break;
			case 3:
				waiting();
				Star();
				Save_Data();
				break;
			default:
				printf("Invalid Choice try again");
		}

	} while(choice != 3);

	return 0;
}

//that function call when Voter want to login or signUp and this is call in main function
void Voter_Panel() {
	int choice;

	do {
		printf("\n\t\t\t\t\t---- Voter Panel ----\n\n");
		printf("1:	Voter Signup\n");
		printf("2:	Voter Login\n");
		printf("3:	Go Back <---\n");
		printf("4:	Exit\n");

		printf("\n\t\t\tChoice: ");
		scanf("%d",&choice);

		switch(choice) {
			case 1:
				waiting();
				Star();
				SignUp();
				break;
			case 2:
				waiting();
				Star();
				Login();
				break;
			case 3:
				waiting();
				Star();
				Save_Data();
				break;
			case 4:
				Star();
				Save_Data();
				exit(0);
				break;
			default:
				printf("Invalid Choice try again");
		}
	} while(choice != 3);
}

//this function is made for Voter SignUp when voter choose SignUp in Function Named login_Or_SignUp and this function is call in that function is call in login_Or_SignUp function
void SignUp() {
	struct voter new_Voter;
	bool found = true;

	printf("\n\t\t\t\t\t---- SignUp ----\n\n");
	getchar(); //buffer Control
	
	printf("Name: ");
	gets(new_Voter.V_name);
	printf("Address: ");
	gets(new_Voter.V_address);
	printf("Mobile No: ");
	gets(new_Voter.V_Mobile_number);

	printf("Age: ");
	scanf("%d",&new_Voter.age);
	
	getchar(); //buffer Control

	while(found == true) {
		if(new_Voter.age>=18) {

			bool check = true;
			printf("CNIC: ");
			gets(new_Voter.V_CNIC);

			while(strlen(new_Voter.V_CNIC) != 15 || new_Voter.V_CNIC[5] != '-' || new_Voter.V_CNIC[13] != '-') {
				printf("Invalid CNIC Try Again\nCNIC: ");
				gets(new_Voter.V_CNIC);
			}

			for(int i=0; i < VoterCount; i++) {
				if(strcmp(voters[i].V_CNIC, new_Voter.V_CNIC) == 0) {
					check = false;
					break;
				}
			}

			if(check == false) {
				printf("CNIC already exists!\n");
				found = true;
			} else {
				new_Voter.IsVoted = 0;
				voters[VoterCount++] = new_Voter;
				printf("\n\t\t\t\t\tDetail Added SuccessFully!\n");
				Save_Data();
				found = false;
			}

		} else {
			printf("You Are Not Eligible to cast Vote");
			found = false;
		}
	}


}

////this function is made for Voter Login when voter choose Login in Function Named login_Or_SignUp and this function is call in that function is call in login_Or_SignUp function
void Login() {
	char CNIC[20];
	bool check = true;
	int choice;

	printf("\n\t\t\t\t\t---- Login ----\n\n");
	getchar(); //buffer Control
	
	printf("CNIC: ");
	gets(CNIC);

	while(strlen(CNIC) != 15 || CNIC[5] != '-' || CNIC[13] != '-') {
		printf("Invalid CNIC Try Again\nCNIC: ");
		gets(CNIC);
	}

	for(int i=0; i < VoterCount; i++) {
		if(strcmp(voters[i].V_CNIC, CNIC) == 0) {
			check = false;
			currentVoterIndex = i;
			break;
		}
	}

	if(check == false) {
		printf("\n\t\t\t\t\t---- Successfully Logined ----\n\n");
		do {
			waiting();
			Star();
			printf("\n\t\t\t\t\t---- Main Menu ----\n\n");
			printf("1: View Electoral System Info\n");
			printf("2: Cast Vote\n");
			printf("3: View Election Results\n");
			printf("4: Go Back <---\n");
			printf("5: Exits\n");

			printf("\n\t\t\tChoice: ");
			scanf("%d", &choice);

			switch(choice) {
				case 1:

					waiting();
					Star();
					DisplayElectoralSystem();
					break;
				case 2:
					waiting();
					Star();
					CastVote();
					break;
				case 3:
					waiting();
					Star();
					DisplayResults();
					break;
				case 4:
					waiting();
					Star();
					Save_Data();
					break;
				case 5:
					waiting();
					Star();
					Save_Data();
					exit(0);
					break;
				default:
					printf("Invalid Choice try again");
			}
		} while(choice != 5);

	} else {
		printf("\n\n\n\t\t\t\t Account Not Found!\n");
		printf("\t\t\t\t SignUp or Try Again!\n");
	}

}

void DisplayElectoralSystem() {
	char choice;
	getchar();
	printf("\n\t\t\t\t\t---- Electoral System ----\n\n");
	printf("a. National Assembly: 272 FPTP seats\n");
	printf("   Punjab(141), Sindh(61), KP(45), Balochistan(16), ICT(3)\n");
	printf("b. Reserved Seats: Women(60), Minorities(10) via PR\n");
	printf("c. Senate: 104 seats (indirect election)\n");

	printf("Return to Main Menu (Y/N): ");
	scanf("%c",&choice);

	if(choice == 'Y' || choice == 'y') {
		return;
	} else if(choice == 'N' || choice == 'n') {
		printf("\n\n\t\t\t\t\t Wait Time 8 sec");
		Sleep(8*1000);
	}



}

void CastVote() {
	int UserChoice;
	printf("\n\t\t\t\t\t---- Casting Vote Penel ----\n\n");

	if (voters[currentVoterIndex].IsVoted) {
		printf("You have already cast your vote!\n");
		return;
	}
	
	for (int i = 0; i < CandidateCount; i++) {
        printf("%d. Name: %s \n   Party: %s\n", i + 1, candidates[i].C_Name, candidates[i].C_Party);
    }

    printf("\n\t\t\tChoose (1-%d): ", CandidateCount);
    scanf("%d", &UserChoice);

    if (UserChoice >= 1 && UserChoice <= CandidateCount) {
        candidates[UserChoice - 1].vote++;
        voters[currentVoterIndex].IsVoted = 1;
        Save_Data();
        printf("\n\t\t\t\t\t---- Vote Casted Successfully ----\n\n");
    } else {
        printf("Invalid choice. Vote not recorded.\n");
    }


}

//Admin Portion Start
void Admin_Panel() {
	int choice;
	do {
		printf("\n\t\t\t\t\t---- Admin Panel ----\n\n");
		printf("1:	Admin Signup\n");
		printf("2:	Admin Login\n");
		printf("3:	Go Back <---\n");
		printf("4:	Exit\n");

		printf("\n\t\t\tChoice: ");
		scanf("%d",&choice);

		switch(choice) {
			case 1:
				waiting();
				Star();
				Admin_SignUp();
				break;
			case 2:
				waiting();
				Star();
				Admin_Login();
				break;
			case 3:
				waiting();
				Star();
				Save_Data();
				break;
			case 4:
				Star();
				Save_Data();
				exit(0);
				break;
			default:
				printf("Invalid Choice try again");
		}
	} while(choice != 3);

}

void Admin_SignUp() {
	printf("\n\t\t\t\t\t---- Admin SignUp ----\n\n");
	getchar(); //Buffer Control
	if(AdminCount == 0) {
		printf("Name: ");
		gets(admin_info.Admin_Name);

		printf("Password: ");
		gets(admin_info.Admin_Password);

		AdminCount=1;
	} else {
		printf("Admin already Exist");
	}
	Save_Data();
}

void Admin_Login() {
	char name[50];
	char Password[50];

	printf("\n\t\t\t\t\t---- Admin Login ----\n\n");
	getchar(); //Buffer Control
	printf("Name: ");
	gets(name);

	printf("Password: ");
	gets(Password);

	if(strcmp(name,admin_info.Admin_Name)==0 && strcmp(Password, admin_info.Admin_Password) == 0) {
		printf("\n\t\t\t\t\t---- Successfully Logined ----\n\n");
		int choice;
		do {
			waiting();
			Star();
			printf("\n\t\t\t\t\t---- Admin Main Menu ----\n\n");
			printf("1: Add Candidate\n");
			printf("2: View Result\n");
			printf("3: Delete Candidate\n");
			printf("4: Update Candidate\n");
			printf("5: Go Back <---\n");
			printf("6: Exits\n");

			printf("\n\t\t\tChoice: ");
			scanf("%d", &choice);

			switch(choice) {
				case 1:
					waiting();
					Star();
					AddCandidate();
					break;
				case 2:
					waiting();
					Star();
					DisplayResults();
					break;
				case 3:
					waiting();
					Star();
					DeleteCandidate();
					break;
				case 4:
					waiting();
					Star();
					UpdateCandidate();
					break;
				case 5:
					waiting();
					Star();
					Save_Data();
					return;
					break;
				case 6:
					waiting();
					Save_Data();
					exit(0);
					break;
				default:
					printf("Invalid Choice try again");
			}
		} while(choice != 5);

	} else {
		printf("\n\t\t\t\t\t---- Admin Not Found ----\n\n");
		waiting();
		Star();
	}
}
void AddCandidate() {
	struct candidate New_Candidate;
	if(CandidateCount>3) {
		printf("\n\t\t\t\t\t---- Candidate Limit Reached ----\n\n");
		return;
	}
	getchar(); //Buffer Control
	printf("Candidate Name: ");
	gets(New_Candidate.C_Name);


	printf("Candidate Party: ");
	gets(New_Candidate.C_Party);

	New_Candidate.vote=0;

	candidates[CandidateCount] = New_Candidate;
	printf("\n\t\t\t\t\t---- Candidate Added Successfully ----\n\n");
	CandidateCount++;

	Save_Data();

}
void DisplayResults() {
	printf("\n--- Election Results ---\n");
	for(int i = 0; i < CandidateCount; i++) {
		printf("%s (%s) - %d votes\n", candidates[i].C_Name, candidates[i].C_Party, candidates[i].vote);
	}
}

// Function to Delete the Candidate Admin Only
void DeleteCandidate() {
    int choice;
    char confirm;

    if (CandidateCount == 0) {
        printf("\n\t\t\t\tNo candidates to delete.\n");
        return;
    }

    printf("\n\t\t\t\t---- Delete Candidate ----\n\n");
    for (int i = 0; i < CandidateCount; i++) {
        printf("%d. %s (%s)\n", i + 1, candidates[i].C_Name, candidates[i].C_Party);
    }

    printf("\nEnter the number of the candidate to delete: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > CandidateCount) {
        printf("Invalid selection.\n");
        return;
    }

    getchar(); // Clear newline
    printf("Are you sure you want to delete '%s'? (Y/N): ", candidates[choice - 1].C_Name);
    scanf("%c", &confirm);

    if (confirm == 'Y' || confirm == 'y') {
        for (int i = choice - 1; i < CandidateCount - 1; i++) {
            candidates[i] = candidates[i + 1];
        }

        CandidateCount--;
        Save_Data();
        printf("Candidate deleted successfully.\n");
    } else {
        printf("Deletion cancelled.\n");
    }
}

//Function to Update the Candidate information
void UpdateCandidate() {
    int choice;
    char confirm;

    if (CandidateCount == 0) {
        printf("\n\t\t\t\tNo candidates to update.\n");
        return;
    }

    printf("\n\t\t\t\t---- Update Candidate ----\n\n");
    for (int i = 0; i < CandidateCount; i++) {
        printf("%d. %s (%s)\n", i + 1, candidates[i].C_Name, candidates[i].C_Party);
    }

    printf("\nEnter the number of the candidate to update: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > CandidateCount) {
        printf("Invalid selection.\n");
        return;
    }

    getchar(); // flush newline
    printf("You selected: %s (%s)\n", candidates[choice - 1].C_Name, candidates[choice - 1].C_Party);
    printf("Are you sure you want to update this candidate? (Y/N): ");
    scanf("%c", &confirm);

    if (confirm == 'Y' || confirm == 'y') {
        getchar(); // flush newline
        printf("Enter new name: ");
        gets(candidates[choice - 1].C_Name);
        printf("Enter new party: ");
        gets(candidates[choice - 1].C_Party);

        Save_Data();
        printf("Candidate updated successfully.\n");
    } else {
        printf("Update cancelled.\n");
    }
}

//this function is call in every fuction because its neccessary to save data. this function save data in file ;
void Save_Data() {
	DVS = fopen("Digital voting system.txt", "w");
	if(DVS == NULL) {
		printf("Error in opening file to save data.\n");
		return;
	}

	//Save the Voter Information
	for (int i = 0; i < VoterCount; i++) {
		fprintf(DVS, "Name: %s\n", voters[i].V_name);
		fprintf(DVS, "Address: %s\n", voters[i].V_address);
		fprintf(DVS, "CNIC: %s\n", voters[i].V_CNIC);
		fprintf(DVS, "Mobile Number: %s\n", voters[i].V_Mobile_number);
		fprintf(DVS, "Age: %d\n", voters[i].age);
		fprintf(DVS, "IsVoted: %d\n", voters[i].IsVoted);

	}

	//save the Candidate Information
	fprintf(DVS, "\n\nCandidateCount: %d\n", CandidateCount);
	for (int i = 0; i < CandidateCount; i++) {
		fprintf(DVS, "Candidate: %s %s %d\n", candidates[i].C_Name, candidates[i].C_Party, candidates[i].vote);
	}

	//Save Admin Information
	fprintf(DVS, "\n\nAdmin Name: %s\n", admin_info.Admin_Name);
	fprintf(DVS, "Admin Password: %s\n", admin_info.Admin_Password);
	fprintf(DVS, "Admin Count: %d\n", AdminCount);


	fclose(DVS);
}


//this function is made to load data mean read the file before program start because file save data every time program compile. So its neccessary to read all data to avoid Multiple attemp
void Load_Data() {
	DVS = fopen("Digital voting system.txt", "r");
	if (DVS == NULL) {
		return;
	}

	//load Voter information
	while (fscanf(DVS, "Name: %[^\n]\n", voters[VoterCount].V_name) == 1) {
    fscanf(DVS, "Address: %[^\n]\n", voters[VoterCount].V_address);
    fscanf(DVS, "CNIC: %[^\n]\n", voters[VoterCount].V_CNIC);
    fscanf(DVS, "Mobile Number: %[^\n]\n", voters[VoterCount].V_Mobile_number);
    fscanf(DVS, "Age: %d\n", &voters[VoterCount].age);
    fscanf(DVS, "IsVoted: %d\n", &voters[VoterCount].IsVoted);
    VoterCount++;
}


	//load the Candidate information
	fscanf(DVS, "CandidateCount: %d\n", &CandidateCount);
	for (int i = 0; i < CandidateCount; i++) {
		fscanf(DVS, "Candidate: %s %s %d\n", candidates[i].C_Name, candidates[i].C_Party, &candidates[i].vote);
	}

	//load Admin Information
	fscanf(DVS, "Admin Name: %s\n", &admin_info.Admin_Name);
	fscanf(DVS, "Admin Password: %s\n", &admin_info.Admin_Password);
	fscanf(DVS, "Admin Count: %d\n", &AdminCount);

	fclose(DVS);
}

//print loading then clear screen
void waiting() {
	for(int i=1; i<=5; i++) {
		printf("\n");
		if(i==5) {
			printf("\t\t\t\t");
		}
	}
	printf("Loading: ");
	for(int i=1; i<=10; i++) {
		printf("#");
		Sleep(0.1*1000);
	}
	system("cls");
}
//print stars
void Star() {
	printf("\n\t\t");
	for(int i=1; i<=80; i++) {
		printf("*");
	}
	printf("\n");
}
