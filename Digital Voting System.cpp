#include <stdio.h>
#include <string.h> // Required for strcspn
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <ctype.h> // Required for isdigit
#include <conio.h> // for _getch()


// function Related to Voter
void Voter_Panel();
void SignUp();				   // Create Account of Voter
void Login();				   // Voter login
void DisplayElectoralSystem(); // Display the details of Electrol System
void CastVote();			   // voter Cast the vote

// Functions Related to Admin
void Admin_Panel();
void Admin_SignUp();
void Admin_Login(int Count); // Login to Admin Account (THree Chances only)
void AddCandidate();
void ShowCandidateInformation();
void DisplayResults(); // Display the Result in Sorted (Access both Admin & Voters)
void DeleteCandidate();
void UpdateCandidate();
void VoterDetail(); // SHow the Detail of Selected Voter (Search With CNIC)
void ResetVotes();
void clean_mobile(char *src, char *dest); // Clean the Mobile Number to remove any non-digit characters

// Functions Related to Data and Design
void Load_Data();
void Save_Data();
void Star();
void waiting(); // use for design (Loading + Clear Screen)
void getPassword(char *password);

// structure for Admin Information
struct admin {
	char Admin_Name[20];
	char Admin_Password[20];
} admin_info;

int AdminCount = 0; // 1 Admin only

// structure for candidate
struct candidate {
	char C_Name[50];
	char C_Party[30];
	char C_Address[25];
	char C_Education[40];

	int vote;
} candidates[4];

int CandidateCount = 0;

// Structure for Voter Information
struct voter {
	char V_name[100];
	char V_address[100];
	char V_Mobile_number[20];
	int age;
	char V_CNIC[20];
	int IsVoted;

} voters[2000];

int VoterCount = 0;			// count for voter that How many Accounts added
int currentVoterIndex = -1; // store the index of Voter Index so he/She login

// Files to store data of specific Peoples
FILE *Voter;
FILE *Admin;
FILE *Candidate;

int main() {
	system("color F1"); // change the console Background and text color  white:blue
	Load_Data();
	int choice = 0;

	do {
		printf("\n\t\t\t\t\t---- Digital Voting System ----\n");
		printf("\t\t\t\t\t     +++ Main Panel +++\n\n\n");
		printf("1:	Voter Panel\n");
		printf("2:	Admin Panel\n");
		printf("3:	Exit\n");

		printf("\n\t\t|| Choice: ");
		scanf("%d", &choice);

		switch (choice) {
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
				printf("\n\t\t\t\t\t ---- Thank You %c ----\n", 3);
				Save_Data();
				break;
			default:
				printf("Invalid Choice try again");
		}

	} while (choice != 3);

	return 0;
}

//masking the password
void getPassword(char *password) {
	int i = 0;
	char ch;
	bool show = false;  // Toggle flag

	while (1) {
		ch = _getch();

		if (ch == 13) { // ENTER key
			break;
		} else if (ch == 9) { // TAB key toggles full visibility
			show = !show;
			printf("\rPassword: ");
			for (int j = 0; j < i; j++) {
				if (show)
					printf("%c", password[j]);
				else
					printf("*");
			}
		} else if (ch == 8) { // BACKSPACE
			if (i > 0) {
				i--;
				printf("\b \b");
			}
		} else if (i < 19 && isprint(ch)) {
			password[i++] = ch;
			if (show)
				printf("%c", ch);
			else
				printf("*");
		}
	}
	password[i] = '\0';
	printf("\n");
}

// that function call when Voter want to login or signUp and this is call in main function
void Voter_Panel() {
	int choice;

	do {
		printf("\n\t\t\t\t\t---- Voter Panel ----\n\n");
		printf("1:	Voter Signup\n");
		printf("2:	Voter Login\n");
		printf("3:	Go Back <---\n");
		printf("4:	Exit\n");

		printf("\n\t\t\tChoice: ");
		scanf("%d", &choice);

		switch (choice) {
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
				printf("\n\t\t\t\t\t---- Returning Back to Main Panel ----\n");
				Save_Data();
				break;
			case 4:
				waiting();
				Star();
				Save_Data();
				printf("\n\t\t\t\t\t---- Thank You %c ----\n", 3);
				exit(0);
				break;
			default:
				printf("Invalid Choice try again");
		}
	} while (choice != 3);
}

// this function is made for Voter SignUp when voter choose SignUp in Function Named login_Or_SignUp and this function is call in that function is call in login_Or_SignUp function
void SignUp() {
	struct voter new_Voter;

	printf("\n\t\t\t\t\t---- SignUp ----\n\n");
	getchar(); // buffer Control

	// Check if the voter limit is reached
	if (VoterCount >= 2000) {
		printf("Voter limit reached!\n");
		return;
	}

	printf("Name: ");
	fgets(new_Voter.V_name, sizeof(new_Voter.V_name), stdin);
	new_Voter.V_name[strcspn(new_Voter.V_name, "\n")] = 0; // Remove newline

	printf("Address: ");
	fgets(new_Voter.V_address, sizeof(new_Voter.V_address), stdin);
	new_Voter.V_address[strcspn(new_Voter.V_address, "\n")] = 0; // Remove newline

	// Validate Mobile Number
	char cleaned_mobile[25];
	while (1) {
		printf("Mobile No: ");
		fgets(new_Voter.V_Mobile_number, sizeof(new_Voter.V_Mobile_number), stdin);
		new_Voter.V_Mobile_number[strcspn(new_Voter.V_Mobile_number, "\n")] = 0; // Remove newline

		clean_mobile(new_Voter.V_Mobile_number, cleaned_mobile);

		int valid = 0;
		int len = strlen(cleaned_mobile);

		if ((strncmp(cleaned_mobile, "+92", 3) == 0 && len == 13) || // +92XXXXXXXXXX
		        (strncmp(cleaned_mobile, "0092", 4) == 0 && len == 14) || // 0092XXXXXXXXXX
		        (strncmp(cleaned_mobile, "03", 2) == 0 && len == 11){  // 03XXXXXXXXX
		        valid = 1;
	}

if (valid)
		break;
	else
		printf("Invalid Mobile Number! Please enter a valid Pakistani mobile number.\n");
}

while(1) {

	printf("Age: ");
	scanf("%d", &new_Voter.age);

	if (new_Voter.age > 115) {
		printf("Invalid Age!! try Again (1-115)\n ");
	}
	else
	{
		break;
	}
}
getchar(); // buffer Control

if (new_Voter.age < 18) {
	printf("You must be at least 18 years old to register.\n");
	return;
}

bool check = true;
printf("CNIC: ");
fgets(new_Voter.V_CNIC, sizeof(new_Voter.V_CNIC), stdin);
new_Voter.V_CNIC[strcspn(new_Voter.V_CNIC, "\n")] = 0;

while (strlen(new_Voter.V_CNIC) != 15 || new_Voter.V_CNIC[5] != '-' || new_Voter.V_CNIC[13] != '-') {
	printf("Invalid CNIC Try Again\nCNIC: ");
	fgets(new_Voter.V_CNIC, sizeof(new_Voter.V_CNIC), stdin);
	new_Voter.V_CNIC[strcspn(new_Voter.V_CNIC, "\n")] = 0;
}

for (int i = 0; i < VoterCount; i++) {
	if (strcmp(voters[i].V_CNIC, new_Voter.V_CNIC) == 0) {
		check = false;
		break;
	}
}

if (check == false) {
	printf("CNIC already exists!\n");
} else {
	new_Voter.IsVoted = 0;
	voters[VoterCount++] = new_Voter;
	printf("\n\t\t\t\t\tDetail Added SuccessFully!\n");
	Save_Data();
}
}

// this function is made for Voter Login when voter choose Login in Function Named login_Or_SignUp and this function is call in that function is call in login_Or_SignUp function
void Login() {
	char CNIC[20];
	bool check = false; // check for user account already Exist or not
	int choice;

	printf("\n\t\t\t\t\t---- Login ----\n\n");
	getchar(); // buffer Control

	printf("CNIC: ");
	fgets(CNIC, sizeof(CNIC), stdin);
	CNIC[strcspn(CNIC, "\n")] = 0;

	while (strlen(CNIC) != 15 || CNIC[5] != '-' || CNIC[13] != '-') {
		printf("Invalid CNIC Try Again\nCNIC: ");
		fgets(CNIC, sizeof(CNIC), stdin);
		CNIC[strcspn(CNIC, "\n")] = 0;
	}

	for (int i = 0; i < VoterCount; i++) {
		if (strcmp(voters[i].V_CNIC, CNIC) == 0) {
			check = true; // CNIC found mean Voter have Account
			currentVoterIndex = i;
			break;
		}
	}

	if (check == true) {
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

			switch (choice) {
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
					printf("\n\t\t\t\t\t---- Returning Back to Voter Panel ----\n");
					Save_Data();
					break;
				case 5:
					waiting();
					Star();
					Save_Data();
					printf("\n\t\t\t\t\t---- Thank You %c ----\n", 3);
					exit(0);
					break;
				default:
					printf("Invalid Choice try again");
			}
		} while (choice != 4);
	} else {
		printf("\n\n\n\t\t\t\t CNIC Not Matched!\n");
		int Selection; // selection of choice
		printf("1. SignUp\n2. Try Again!\n");
		scanf("%d", &Selection);

		if (Selection == 1)
			SignUp();
		else if (Selection == 2)
			Login(); // Recursion
		else
			printf("Invalid Choice try again");
	}
}

// Display the information of Election system That how it works
void DisplayElectoralSystem() {
	char choice;
	getchar();
	printf("\n\t\t\t\t\t---- Electoral System ----\n\n");
	printf("a. National Assembly: 272 FPTP seats\n");
	printf("   Punjab(141), Sindh(61), KP(45), Balochistan(16), ICT(3)\n");
	printf("b. Reserved Seats: Women(60), Minorities(10) via PR\n");
	printf("c. Senate: 104 seats (indirect election)\n");

	printf("Return to Main Menu (Y/N): ");
	scanf("%c", &choice);

	if (choice == 'Y' || choice == 'y') {
		return;
	} else if (choice == 'N' || choice == 'n') {
		printf("\n\n\t\t\t\t\t Wait Time 8 sec");
		Sleep(8 * 1000);
	}
}

// Voter can Cast Vote to there Fav Candidate
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

// Admin Portion Start
void Admin_Panel() {
	int choice;
	do {
		printf("\n\t\t\t\t\t---- Admin Panel ----\n\n");
		printf("1:	Admin Signup\n");
		printf("2:	Admin Login\n");
		printf("3:	Go Back <---\n");
		printf("4:	Exit\n");

		printf("\n\t\t\tChoice: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				waiting();
				Star();
				Admin_SignUp();
				break;
			case 2:
				waiting();
				Star();
				Admin_Login(1);
				break;
			case 3:
				waiting();
				Star();
				printf("\n\t\t\t\t\t---- Returning Back to Main Panel  ----\n");
				Save_Data();
				break;
			case 4:
				Star();
				Save_Data();
				printf("\n\t\t\t\t\t---- Thank You %c ----\n", 3);
				exit(0);
				break;
			default:
				printf("Invalid Choice try again");
		}
	} while (choice != 3);
}

// Admin Create An Account Here
void Admin_SignUp() {
	printf("\n\t\t\t\t\t---- Admin SignUp ----\n\n");
	getchar(); // Buffer Control
	if (AdminCount == 0) {
		printf("Name: ");
		fgets(admin_info.Admin_Name, sizeof(admin_info.Admin_Name), stdin);
		admin_info.Admin_Name[strcspn(admin_info.Admin_Name, "\n")] = 0;

		printf("Password (press Tab to Show/hide): ");
		getPassword(admin_info.Admin_Password);


		AdminCount = 1;
	} else {
		printf("Admin already Exist");
	}

	Save_Data();
}

// Admin Access His/her Account
void Admin_Login(int Count) {
	char name[50];
	char Password[50];

	printf("\n\t\t\t\t\t---- Admin Login ----\n\n");
	getchar(); // Buffer Control
	printf("Name: ");
	fgets(name, sizeof(name), stdin);
	name[strcspn(name, "\n")] = 0;

	printf("Password (press Tab to Show/hide): ");
	getPassword(Password);


	if (strcmp(name, admin_info.Admin_Name) == 0 && strcmp(Password, admin_info.Admin_Password) == 0) {
		printf("\n\t\t\t\t\t---- Successfully Logined ----\n\n");
		int choice;
		do {
			waiting();
			Star();
			printf("\n\t\t\t\t\t---- Admin Main Menu ----\n\n");
			printf("1: Add Candidate\n");
			printf("2: View Result\n");
			printf("3: Show Candidate Details\n");
			printf("4: Delete Candidate\n");
			printf("5: Update Candidate\n");
			printf("6: Show Voter Detail\n");
			printf("7: Reset Vote\n");
			printf("8: Go Back <---\n");
			printf("9: Exits\n");

			printf("\n\t\t\tChoice: ");
			scanf("%d", &choice);

			switch (choice) {
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
					ShowCandidateInformation();
					break;
				case 4:
					waiting();
					Star();
					DeleteCandidate();
					break;
				case 5:
					waiting();
					Star();
					UpdateCandidate();
					break;
				case 6:
					waiting();
					Star();
					VoterDetail();
					break;
				case 7:
					waiting();
					Star();
					ResetVotes();
					break;
				case 8:
					waiting();
					Star();
					printf("\n\t\t\t\t\t---- Returning Back to Admin Panel  ----\n");
					Save_Data();
					return;
					break;
				case 9:
					waiting();
					Save_Data();
					printf("\n\t\t\t\t\t---- Thank You %c ----\n", 3);
					exit(0);
					break;
				default:
					printf("Invalid Choice try again");
			}
		} while (choice != 5);
	} else {
		if (Count < 3) {

			if (strcmp(name, admin_info.Admin_Name) != 0) {
				printf("\n\t\t\t\t\t---- Invalid Admin Name ----\n\n");
			} else {
				printf("\n\t\t\t\t\t---- Invalid Admin Password ----\n\n");
			}
			Count++;
			Admin_Login(Count);
		} else {
			printf("\n\t\t\t\t\t---- Limit Reached ----\n\n");
			return;
		}
	}
}

// Admin Add an Candidate
void AddCandidate() {
	struct candidate New_Candidate;
	if (CandidateCount > 3) {
		printf("\n\t\t\t\t\t---- Candidate Limit Reached ----\n\n");
		return;
	}
	getchar(); // Buffer Control
	printf("Candidate Name: ");
	fgets(New_Candidate.C_Name, sizeof(New_Candidate.C_Name), stdin);
	New_Candidate.C_Name[strcspn(New_Candidate.C_Name, "\n")] = 0;

	printf("Candidate Party: ");
	fgets(New_Candidate.C_Party, sizeof(New_Candidate.C_Party), stdin);
	New_Candidate.C_Party[strcspn(New_Candidate.C_Party, "\n")] = 0;

	printf("Candidate Address: ");
	fgets(New_Candidate.C_Address, sizeof(New_Candidate.C_Address), stdin);
	New_Candidate.C_Address[strcspn(New_Candidate.C_Address, "\n")] = 0;

	printf("Candidate Education: ");
	fgets(New_Candidate.C_Education, sizeof(New_Candidate.C_Education), stdin);
	New_Candidate.C_Education[strcspn(New_Candidate.C_Education, "\n")] = 0;

	New_Candidate.vote = 0;

	candidates[CandidateCount] = New_Candidate;
	printf("\n\t\t\t\t\t---- Candidate Added Successfully ----\n\n");
	CandidateCount++;

	Save_Data();
}

// Display the Result with Candidate, Name Party and Vote
void DisplayResults() {
	struct candidate sortedCandidates[4];

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // Handle to control console color

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(h, &csbi);

	WORD originalAttr = csbi.wAttributes;  // Save original attribute
	WORD background = originalAttr & 0xF0; // Extract background (e.g., F0 from F1)

	int TotalVotes = 0;

	// Copy candidate data
	for (int i = 0; i < CandidateCount; i++) {
		sortedCandidates[i] = candidates[i];
		TotalVotes += candidates[i].vote;
	}

	// Sort by votes (descending)
	for (int i = 0; i < CandidateCount - 1; i++) {
		for (int j = 0; j < CandidateCount - i - 1; j++) {
			if (sortedCandidates[j].vote < sortedCandidates[j + 1].vote) {
				struct candidate temp = sortedCandidates[j];
				sortedCandidates[j] = sortedCandidates[j + 1];
				sortedCandidates[j + 1] = temp;
			}
		}
	}

	printf("\n\t\t\t\t\t--- Election Results ---\n\n");

	for (int i = 0; i < CandidateCount; i++) {
		float percent = 0;
		if (TotalVotes > 0)
			percent = ((float)sortedCandidates[i].vote / TotalVotes) * 100;

		// Reset text color before printing candidate info
		SetConsoleTextAttribute(h, originalAttr);
		printf("\t\t%s (%s) - %d votes\n", sortedCandidates[i].C_Name, sortedCandidates[i].C_Party, sortedCandidates[i].vote);

		// Determine bar color based on percentage
		WORD barColor;
		if (percent > 50)
			barColor = 10; // Bright Green
		else if (percent > 30)
			barColor = 9; // Bright Blue
		else if (percent > 15)
			barColor = 14; // Yellow
		else
			barColor = 12; // Bright Red

		// Apply foreground color + keep background
		SetConsoleTextAttribute(h, background | barColor);

		printf("\t\t    |");
		int barLength = (int)(percent / 2); // Max 50 blocks
		for (int j = 0; j < barLength; j++) {
			printf("%c", 219);
		}

		// Reset to original color
		SetConsoleTextAttribute(h, originalAttr);
		printf(" (%.2f%%)\n\n", percent);
	}

	SetConsoleTextAttribute(h, originalAttr); // reset to orignal color
	printf("\n\n\t\t\t\tWaiting for 5 sec!!");
	Sleep(5 * 1000);
}

// Show all the Information of Candidate to Admin
void ShowCandidateInformation() {
	printf("\n\t\t\t\t\t---- Information of Candidates ----\n\n");
	for (int i = 0; i < CandidateCount; i++) {
		printf("Name: %s\n", candidates[i].C_Name);
		printf("Party: %s\n", candidates[i].C_Party);
		printf("Address: %s\n", candidates[i].C_Address);
		printf("Education: %s\n", candidates[i].C_Education);
		printf("Vote: %d\n\n", candidates[i].vote);
	}

	printf("\n\n\t\t\t\tWaiting for 5 sec!!");
	Sleep(5 * 1000);
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

	// show all added Candidates
	for (int i = 0; i < CandidateCount; i++) {
		printf("%d. %s (%s)\n", i + 1, candidates[i].C_Name, candidates[i].C_Party);
	}

	printf("\nEnter the number of the candidate to delete: ");
	scanf("%d", &choice);

	// if choice or selection is Invalid
	if (choice < 1 || choice > CandidateCount) {
		printf("Invalid selection.\n");
		return;
	}

	getchar(); // buffer Control

	// confirm from Admin That are you sure you want to delete the Candidate with name If Yes(y) delete otherwise not
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

// Function to Update the Candidate information
void UpdateCandidate() {
	int choice;
	char confirm;

	// check for candidate if no candidate is added before return to admin panel
	if (CandidateCount == 0) {
		printf("\n\t\t\t\tNo candidates to update.\n");
		return;
	}

	printf("\n\t\t\t\t---- Update Candidate ----\n\n");

	// display all candidates to select the candidate for update
	for (int i = 0; i < CandidateCount; i++) {
		printf("%d. %s (%s)\n", i + 1, candidates[i].C_Name, candidates[i].C_Party);
	}

	printf("\nEnter the number of the candidate to update: ");
	scanf("%d", &choice);

	// if choice or selection is Invalid
	if (choice < 1 || choice > CandidateCount) {
		printf("Invalid selection.\n");
		return;
	}

	getchar(); // Buffer Control

	printf("You selected: %s (%s)\n", candidates[choice - 1].C_Name, candidates[choice - 1].C_Party); // give information about selected candidate
	printf("Are you sure you want to update this candidate? (Y/N): ");								  // confirm about update
	scanf("%c", &confirm);

	if (confirm == 'Y' || confirm == 'y') {
		getchar(); // flush newline
		printf("Enter new name: ");
		fgets(candidates[choice - 1].C_Name, sizeof(candidates[choice - 1].C_Name), stdin);
		candidates[choice - 1].C_Name[strcspn(candidates[choice - 1].C_Name, "\n")] = 0;

		printf("Enter new party: ");
		fgets(candidates[choice - 1].C_Party, sizeof(candidates[choice - 1].C_Party), stdin);
		candidates[choice - 1].C_Party[strcspn(candidates[choice - 1].C_Party, "\n")] = 0;

		printf("Enter new Address: ");
		fgets(candidates[choice - 1].C_Address, sizeof(candidates[choice - 1].C_Address), stdin);
		candidates[choice - 1].C_Address[strcspn(candidates[choice - 1].C_Address, "\n")] = 0;

		printf("Enter new Education: ");
		fgets(candidates[choice - 1].C_Education, sizeof(candidates[choice - 1].C_Education), stdin);
		candidates[choice - 1].C_Education[strcspn(candidates[choice - 1].C_Education, "\n")] = 0;

		Save_Data();
		printf("Candidate updated successfully.\n");
	} else {
		printf("Update cancelled.\n");
	}
}

// Search For Voter And Show his/her All details
void VoterDetail() {
	char CNIC[20];
	int Index;
	bool found = false; // voter check

	printf("\n\t\t\t\t\t---- Voter Details ----\n\n");
	getchar(); // buffer Control

	printf("Searching For Voter Please enter His/Her CNIC: ");
	fgets(CNIC, sizeof(CNIC), stdin);
	CNIC[strcspn(CNIC, "\n")] = 0;

	// check the Syntex Of CNIC
	while (strlen(CNIC) != 15 || CNIC[5] != '-' || CNIC[13] != '-') {
		printf("Invalid CNIC Try Again\nCNIC: ");
		fgets(CNIC, sizeof(CNIC), stdin);
		CNIC[strcspn(CNIC, "\n")] = 0;
	}

	for (int i = 0; i < VoterCount; i++) {
		if (strcmp(voters[i].V_CNIC, CNIC) == 0) {
			Index = i; // CNIC matched and we store the user index

			found = true;
			break; // not need to check further so we stop the loop
		}
	}

	if (found == true) {
		printf("Name: %s\n", voters[Index].V_name);
		printf("CNIC: %s\n", voters[Index].V_CNIC);
		printf("Address: %s\n", voters[Index].V_address);
		printf("Mobile Number: %s\n", voters[Index].V_Mobile_number);
		printf("Age: %d\n", voters[Index].age);
		printf("IsVoted: %d\n", voters[Index].IsVoted);

		printf("\n\n\t\t\t\tWaiting for 5 sec!!");
		Sleep(5 * 1000);
	} else {
		printf("Voter Not Found");
	}
}

void ResetVotes() {
	printf("\n\n\t\t\t\t Reseting");

	for (int i = 0; i < VoterCount; i++) {
		voters[i].IsVoted = 0;
	}

	for (int i = 0; i < CandidateCount; i++) {
		candidates[i].vote = 0;
	}

	for (int i = 1; i <= 10; i++) {
		printf(".");
		Sleep(0.2 * 1000);
	}

	printf("\n\n\t\t\t\t Data Reset Successfully \n\n");
}

// this function is call in every fuction because its neccessary to save data. this function save data in file ;
void Save_Data() {
	Voter = fopen("Voter.txt", "w");
	Admin = fopen("Admin.txt", "w");
	Candidate = fopen("Candidate.txt", "w");

	if (Voter == NULL) {
		printf("Error in opening Voter file to save data.\n");
		return;
	}

	// Save the Voter Information
	fprintf(Voter, "VoterCount: %d\n", VoterCount);
	for (int i = 0; i < VoterCount; i++) {
		fprintf(Voter, "Name: %s\n", voters[i].V_name);
		fprintf(Voter, "Address: %s\n", voters[i].V_address);
		fprintf(Voter, "CNIC: %s\n", voters[i].V_CNIC);
		fprintf(Voter, "Mobile Number: %s\n", voters[i].V_Mobile_number);
		fprintf(Voter, "Age: %d\n", voters[i].age);
		fprintf(Voter, "IsVoted: %d\n", voters[i].IsVoted);
	}

	// save the Candidate Information
	if (Candidate == NULL) {
		printf("Error in opening Candidate file to save data.\n");
		return;
	}
	fprintf(Candidate, "CandidateCount: %d\n", CandidateCount);
	for (int i = 0; i < CandidateCount; i++) {
		fprintf(Candidate, "Candidate Name: %s\n", candidates[i].C_Name);
		fprintf(Candidate, "Candidate Party: %s\n", candidates[i].C_Party);
		fprintf(Candidate, "Candidate Address: %s\n", candidates[i].C_Address);
		fprintf(Candidate, "Candidate Education: %s\n", candidates[i].C_Education);
		fprintf(Candidate, "Candidate Vote: %d\n", candidates[i].vote);
	}

	// Save Admin Information
	if (Admin == NULL) {
		printf("Error in opening Admin file to save data.\n");
		return;
	}

	fprintf(Admin, "Admin Name: %s\n", admin_info.Admin_Name);
	fprintf(Admin, "Admin Password: %s\n", admin_info.Admin_Password);
	fprintf(Admin, "Admin Count: %d\n", AdminCount);

	fclose(Voter);
	fclose(Candidate);
	fclose(Admin);
}

// this function is made to load data mean read the file before program start because file save data every time program compile. So its neccessary to read all data to avoid Multiple attemp
void Load_Data() {
	Voter = fopen("Voter.txt", "r");
	Candidate = fopen("Candidate.txt", "r");
	Admin = fopen("Admin.txt", "r");

	char buffer[200];

	if (Voter == NULL || Admin == NULL || Candidate == NULL) {
		printf("Error opening one or more files.\n");
		exit(1);
	}

	if (Voter != NULL) {
		fgets(buffer, sizeof(buffer), Voter);
		sscanf(buffer, "VoterCount: %d", &VoterCount);

		for (int i = 0; i < VoterCount; i++) {
			fgets(buffer, sizeof(buffer), Voter);
			sscanf(buffer, "Name: %[^\n]", voters[i].V_name);

			fgets(buffer, sizeof(buffer), Voter);
			sscanf(buffer, "Address: %[^\n]", voters[i].V_address);

			fgets(buffer, sizeof(buffer), Voter);
			sscanf(buffer, "CNIC: %[^\n]", voters[i].V_CNIC);

			fgets(buffer, sizeof(buffer), Voter);
			sscanf(buffer, "Mobile Number: %[^\n]", voters[i].V_Mobile_number);

			fgets(buffer, sizeof(buffer), Voter);
			sscanf(buffer, "Age: %d", &voters[i].age);

			fgets(buffer, sizeof(buffer), Voter);
			sscanf(buffer, "IsVoted: %d", &voters[i].IsVoted);
		}

		fclose(Voter);
	}

	if (Candidate != NULL) {
		fgets(buffer, sizeof(buffer), Candidate);
		sscanf(buffer, "CandidateCount: %d", &CandidateCount);

		for (int i = 0; i < CandidateCount; i++) {
			fgets(buffer, sizeof(buffer), Candidate);
			sscanf(buffer, "Candidate Name: %[^\n]", candidates[i].C_Name);

			fgets(buffer, sizeof(buffer), Candidate);
			sscanf(buffer, "Candidate Party: %[^\n]", candidates[i].C_Party);

			fgets(buffer, sizeof(buffer), Candidate);
			sscanf(buffer, "Candidate Address: %[^\n]", candidates[i].C_Address);

			fgets(buffer, sizeof(buffer), Candidate);
			sscanf(buffer, "Candidate Education: %[^\n]", candidates[i].C_Education);

			fgets(buffer, sizeof(buffer), Candidate);
			sscanf(buffer, "Candidate Vote: %d", &candidates[i].vote);
		}

		fclose(Candidate);
	}

	if (Admin != NULL) {
		fgets(buffer, sizeof(buffer), Admin);
		sscanf(buffer, "Admin Name: %[^\n]", admin_info.Admin_Name);

		fgets(buffer, sizeof(buffer), Admin);
		sscanf(buffer, "Admin Password: %[^\n]", admin_info.Admin_Password);

		fgets(buffer, sizeof(buffer), Admin);
		sscanf(buffer, "Admin Count: %d", &AdminCount);

		fclose(Admin);
	}
}

// print loading then clear screen
void waiting() {
	for (int i = 1; i <= 5; i++) {
		printf("\n");
		if (i == 5) {
			printf("\t\t\t\t");
		}
	}
	printf("Loading: ");
	for (int i = 1; i <= 10; i++) {
		printf("%c", 219);
		Sleep(0.1 * 1000);
	}
	system("cls");
}
// print stars
void Star() {
	printf("\n\t\t");
	for (int i = 1; i <= 80; i++) {
		printf("*");
	}
	printf("\n");
}

// Helper function to remove spaces and dashes
void clean_mobile(char *src, char *dest) {
	int j = 0;
	for (int i = 0; src[i] != '\0'; i++) {
		if (isdigit(src[i]) || src[i] == '+') {
			dest[j++] = src[i];
		}
	}
	dest[j] = '\0';
}
