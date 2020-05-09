#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

int gLine = 1;

struct Data {
	char word;
	int num;
	Data( char theWord, int theNum );
}; // struct Data

class Mission {
    private :
		vector<Data> list;
    public :
		bool CreateList();
	    void Paste(ifstream & file);
    	void Digit(char ch);
	    void English(char ch);
	    void Special(char ch);
		void CheckList(char ch, int & standard, bool & success, bool & shift);
}; // class Mission

int main() {
    
	ifstream file( "input.txt" );

	if (!file)
		cout << "input.txt ERROR" << endl;
	else {
		Mission mission;
		if (mission.CreateList()) {
			cout << "輸入任意鍵開始執行 : ";
			char begin;
			begin = cin.get();
			for (int i = 3; i > 0 ; i--) {
				cout << i << endl;
				Sleep(1000);
			} // for
			cout << "---------------------" << endl;
			mission.Paste(file);
			file.close();
		} // if
	} // else

	cout << endl << endl << "END" << endl;
	system("pause");

} // main()

Data::Data(char theWord, int theNum) {
	word = theWord;
	num = theNum;
} // Data::Data()

bool Mission::CreateList() {

	ifstream file("List.txt");

	if (!file) {
		cout << "List.txt ERROR" << endl;
		return false;
	} // if

	char theWord;
	int theNum;

	while (file >> theWord) {
		file >> theNum;
		Data data( theWord, theNum );
		list.push_back(data);
	} // while

	file.close();
	return true;

} // Mission::CreateList()

void Mission::Paste( ifstream & file ) {

	char ch = '\0';

	while ( file.get(ch) ) {
		// if ( gLine >= 163 ) cout << ch ;
		if ('0' <= ch && ch <= '9') Digit( ch );
		else if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z')) English( ch );
		else Special( ch ) ;
		Sleep(5);
	} // while

} // Mission::Paste()

void Mission::Digit(char ch) {

	keybd_event( ch, 0, 0, 0);
	keybd_event( ch, 0, KEYEVENTF_KEYUP, 0);

} // Digit()

void Mission::English(char ch) {

	if ( 'A' <= ch && ch <= 'Z' ) keybd_event(16, 0, 0, 0); // 按下shift
	else ch = ch - 32;

	keybd_event( ch, 0, 0, 0) ;
	keybd_event( ch, 0, KEYEVENTF_KEYUP, 0 );

	keybd_event( 16, 0, KEYEVENTF_KEYUP, 0 ); // 放開shift

} // English()

void Mission::Special(char ch) {

	int standard = -1;
	bool success = true, shift = false;

	switch (ch) {
	    case ' ' :
			standard = 32;
		    break;
	    case '\t' :
			standard = 9;
		    break;
		case '\n' :
			gLine++;
			standard = 13;
			break;
		default :
			CheckList(ch, standard, success, shift);
	} // switch

	if (success) {
		keybd_event(standard, 0, 0, 0);
		keybd_event(standard, 0, KEYEVENTF_KEYUP, 0);
	} // if
	else success = true;

	if (shift) {
		keybd_event(16, 0, KEYEVENTF_KEYUP, 0); // 放開shift
		shift = false;
	} // if

} // Special()

void Mission::CheckList( char ch, int & standard, bool & success, bool & shift) {

	for (int i = 0; i < list.size(); i++) {
		if (ch == list[i].word) {
			if (list[i].num < 0) {
				keybd_event(16, 0, 0, 0); // 按下shift
				shift = true;
				standard = list[i].num * -1;
			} // if
			else standard = list[i].num;
			return;
		} // if
	} // for

	cout << "No This char : " << "[" << ch << "] " << gLine << endl;
	success = false;

} // Mission::CheckList()


