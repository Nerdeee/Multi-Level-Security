#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool isAuthorized(string password, string securitylevel, vector<string> user_passwords, vector<string> users) {
	// make sure user password and sec level match whats in the file
	bool authorized = false;
		for (int i = 0; i < 4; i++) {
			if (securitylevel == users[i] && password == user_passwords[i]) {
				authorized = true;
				break;
			}
			else {
				authorized = false;
			}
		}
	return authorized;
}

void showFiles(int user_security_level) {
	ifstream dummy_files;
	vector<string> file_access_vec;
	vector<string> file_name_vec;
	vector<int> file_sec_level_vec;


	dummy_files.open("filelist.txt");
	if (dummy_files.is_open()) {
		cout << "Successfully opened file. Showing available files: " << endl;
		string file_access = "";
		string file_name = "";
		string sec_level = "";
		while (dummy_files >> file_access >> file_name >> sec_level) {
			int secLevelNumber = stoi(sec_level);

			file_access_vec.push_back(file_access);
			file_name_vec.push_back(file_name);
			file_sec_level_vec.push_back(secLevelNumber);
		}

		cout << "Read/write   File name      Security Level" << endl;
		for (int i = 0; i < file_access_vec.size(); i++) {
			if (user_security_level >= file_sec_level_vec[i] && file_access_vec[i] == "r") {
				cout << file_access_vec[i] << "     -     " << file_name_vec[i] << "     -     " << file_sec_level_vec[i] << endl;
			}
			else if (file_sec_level_vec[i] >= user_security_level && file_access_vec[i] == "w") {
				cout << file_access_vec[i] << "     -     " << file_name_vec[i] << "     -     " << file_sec_level_vec[i] << endl;
			}
			else {
				continue;
			}
		}
	} else {
		cout << "There was a problem opening the file" << endl;
	}
}

int main() {
	vector<string> user_passwords = { "password1", "password2", "password3", "password4" };
	vector<string> users = { "public", "limited", "secret", "topsecret" };
	bool authorized = false;
	while (!authorized) {
		string securitylevel = "";
		string password = "";
		cout << "Enter your security level (Enter 'public', 'limited', 'secret', or 'topsecret')" << endl;
		cin >> securitylevel;
		cout << "Enter the password for your security level" << endl;
		cin >> password;

		authorized = isAuthorized(password, securitylevel, user_passwords, users);
		if (authorized) {
			int user_index = 0;
			for (int i = 0; i < 4; i++) {
				if (securitylevel == users[i] && password == user_passwords[i]) {
					user_index = i;
				}
			}
			showFiles(user_index);
		}
		else {
			cout << "Username or password is incorrect" << endl;
		}
	}
	cout << endl;

}
