
#include "player_player.h"

//---------------------------------------------------------------------------
//other function
void SetColorAndBackground(int ForgC, int BackC)
{
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
	return;
}
int correct_input(int min, int max)
{
	bool is_correct = false;
	string msg;
	int num;
	char* ptr;
	do {
		SetColorAndBackground(2, 0);
		cout << ">> ";
		SetColorAndBackground(14, 0);
		getline(cin, msg);
		msg += "\n";
		num = strtol(msg.c_str(), &ptr, 10);
		if (num == 0)
		{
			SetColorAndBackground(4, 0);
			cout << "\ninvalid input.try again" << endl;
		}
		else if (num<min || num>max)
		{
			SetColorAndBackground(4, 0);
			cout << "\nout of range.try again" << endl;
		}
		else
			is_correct = true;

	} while (!is_correct);
	return num;
}
int correct_input(int min, int max, char input[])
{
	bool is_correct = false;
	int num, cnt = 0;
	do {
		SetColorAndBackground(2, 0);
		cout << ">> ";
		while (1)
		{
			SetColorAndBackground(14, 0);
			char c = _getch();
			input[cnt] = c;
			input[cnt + 1] = '\0';
			if (input[cnt] == '\b')
			{
				cout << "\b \b";
				if (cnt != 0)
				{
					cnt--;
					input[cnt] = '\0';
				}
			}
			else if (input[cnt] != '\r')
			{
				cout << input[cnt];
				cnt++;
			}
			else
			{
				cnt++;
				break;
			}
		}
		input[cnt - 1] = '\0';
		num = atoi(input);
		if (num == 0 && input[0] != '0')
		{
			SetColorAndBackground(4, 0);
			cout << "invalid input.try again" << endl;
			input[0] = '\0';
			cnt = 0;
		}
		else if (num<min || num>max)
		{
			SetColorAndBackground(1, 0);
			cout << "out of range.try again" << endl;
			input[0] = '\0';
			cnt = 0;
		}
		else
			is_correct = true;

	} while (!is_correct);
	return num;
}

//---------------------------------------------------------------------------
//morse functions
void hello()
{
	//convert "hello" string to morse
	Beep(900, 100);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);
	// cin.get();

	Beep(900, 100);
	_sleep(100);
	//cin.get();

	Beep(900, 100);
	_sleep(100);
	Beep(900, 250);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);
	//cin.get();

	Beep(900, 100);
	_sleep(100);
	Beep(900, 250);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);
	//cin.get();

	Beep(900, 250);
	_sleep(100);
	Beep(900, 250);
	_sleep(100);
	Beep(900, 250);
	_sleep(100);
	//cin.get();
}
void bye()
{
	//convert "bye" string to morse
	Beep(900, 250);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);
	//cin.get();

	Beep(900, 250);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);
	Beep(900, 250);
	_sleep(100);
	Beep(900, 250);
	_sleep(100);
	//cin.get();

	Beep(900, 100);
	_sleep(100);
	//cin.get();
}
void the_end()
{
	//convert "the end" string to morse
	Beep(900, 250);
	_sleep(100);
	//cin.get();

	Beep(900, 100);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);
	//cin.get();

	Beep(900, 100);
	_sleep(100);
	// cin.get();

	Beep(900, 100);
	_sleep(100);
	//cin.get();

	Beep(900, 250);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);
	//cin.get();

	Beep(900, 250);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);
	Beep(900, 100);
	_sleep(100);

}

//---------------------------------------------------------------------------
//function of player class 
int player::are_connected = true;

player::player(io_service& io_service)
	:sock(io_service)
{
	sock.connect(tcp::endpoint(address::from_string("127.0.0.1"), 1234));
}

tcp::socket* player::get_sock()
{
	return &sock;
}

void player::registeration()
{
	SetColorAndBackground(1, 0);
	cout << "//OX" << endl;
	SetColorAndBackground(2, 0);
	cout << "Hi! what's your name? >> ";
	SetColorAndBackground(14, 0);
	getline(cin, name);
	write(sock, boost::asio::buffer(name + "\n"));
	SetColorAndBackground(2, 0);
	cout << "registration completed.:)" << endl << endl;
}
void player::choose_opponent()
{
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	string s = buffer_cast<const char*>(buff.data());

	if (s == "two\n")
	{
		write(sock, boost::asio::buffer("null\n"));

		//show options
		playernum = 2;
		SetColorAndBackground(2, 0);
		cout << "choose your opponent :(enter their name)" << endl;

		boost::asio::streambuf buff;
		read_until(sock, buff, "\n");
		string opp_name = buffer_cast<const char*>(buff.data());
		opp_name.erase(std::remove(opp_name.begin(), opp_name.end(), '\n'), opp_name.end());
		cout << "   " << opp_name << endl;
		transform(opp_name.begin(), opp_name.end(), opp_name.begin(), ::tolower);

		//choose opponent
		string msg;
		while (msg != opp_name)
		{
			SetColorAndBackground(2, 0);
			cout << ">>";
			SetColorAndBackground(14, 0);
			getline(cin, msg);
			transform(msg.begin(), msg.end(), msg.begin(), ::tolower);

			if (msg != opp_name)
			{
				SetColorAndBackground(4, 0);
				cout << "invalid input.try again" << endl;
			}
			else
			{
				write(sock, boost::asio::buffer(msg + "\n"));
				SetColorAndBackground(2, 0);
				cout << "pending..." << endl;
			}
		}
	}
	else if (s == "one\n")
	{
		playernum = 1;

		//show request massage
		boost::asio::streambuf buff;
		read_until(sock, buff, "\n");
		string s = buffer_cast<const char*>(buff.data());
		s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
		SetColorAndBackground(2, 0);
		cout << s << " wants to play." << endl;
		cout << "1-Accept" << endl << "2-Decline" << endl;

		//accept or decline
		int m = correct_input(1, 2);
		string msg = to_string(m);
		write(sock, boost::asio::buffer(msg + "\n"));
	}
}
bool player::accept_or_reject()
{
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	string s = buffer_cast<const char*>(buff.data());
	if (s == "1\n")
		return true;
	else
		return false;
}
int player::start_game()
{
	system("cls");
	SetColorAndBackground(1, 0);
	cout << "//OX" << endl;
	SetColorAndBackground(2, 0);
	if (playernum == 1)
	{
		cout << "you are the first player! choose the ground :)(enter its number)." << endl << endl << endl;
		show_all_grounds();
		int num = correct_input(1, 3);
		string msg = to_string(num) + "\n";
		write(sock, boost::asio::buffer(msg));
		return num;
	}
	else if (playernum == 2)
	{
		cout << "you 're the second player.your opponent chose ground :" << endl;
		boost::asio::streambuf buff2;
		read_until(sock, buff2, "\n");
		string msg = buffer_cast<const char*>(buff2.data());
		return atoi(msg.c_str());
	}

}
void player::show_all_grounds()
{
	SetColorAndBackground(6, 0);
	cout << "  O_______O_______O            O_______O_______O            O_______O_______O" << endl;
	cout << "  |       |       |            |       |       |            | \\     |     / |" << endl;
	cout << "  |       |       |            |       |       |            |  O____O____O  |" << endl;
	cout << "  |       |       |            |   O___O___O   |            |  |\\   |   /|  |" << endl;
	cout << "  |       |       |            |   |       |   |            |  | O__O__O |  |" << endl;
	cout << "  |       |       |            |   |       |   |            |  | |     | |  |" << endl;
	cout << "  O_______O_______O            O___O       O___O            O__O_O     O_O__O" << endl;
	cout << "  |       |       |            |   |       |   |            |  | |     | |  |" << endl;
	cout << "  |       |       |            |   |       |   |            |  | O__O__O |  |" << endl;
	cout << "  |       |       |            |   O___O___O   |            |  |/   |   \\|  |" << endl;
	cout << "  |       |       |            |       |       |            |  O____O____O  |" << endl;
	cout << "  |       |       |            |       |       |            | /     |     \\ |" << endl;
	cout << "  O_______O_______O            O_______O_______O            O_______O_______O" << endl << endl;
	cout << "         (1)                          (2)                          (3)          " << endl << endl;
}

void player::playgame(ground gr, int i)
{
	bool whilecnt = false;
	while (1)
	{
		if (playernum == 2 || whilecnt == true)
		{
			read_move(gr, i);
			gr.show_ground(i);
		}
		else
			whilecnt = true;

		int flag = 1;
		char input_num[1000];
		input_num[0] = '\0';
		thread t1(&player::write_move, this, ref(gr), ref(flag), input_num);
		gr.show_ground_timer(i, ref(flag), input_num);
		if (flag == -1)
		{
			SetColorAndBackground(4, 0);
			cout << "Your time is up" << endl;
			t1.detach();
			t1.~thread();
			write(sock, boost::asio::buffer("0\n"));
		}
		else
		{
			t1.join();
			gr.displayClock(gr.get_time(0), gr.get_time(1));
			gr.show_ground(i);
		}
	}
}
void player::write_move(ground& gr, int& flag, char input_num[])
{
	int num = gr.correct_block(input_num);
	string msg = to_string(num) + "\n";
	flag = 0;
	gr.update_ground(num - 1, -1 * (playernum));
	write(sock, boost::asio::buffer(msg));
}
void player::read_move(ground& gr, int n)
{
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	string s = buffer_cast<const char*>(buff.data());
	int num = 0, state = 3;
	sscanf_s(s.c_str(), "%d\n-%d-%d", &num, &state, &are_connected);
	if (state != playernum && num != 0 && !(playernum == 1 && n == 1 && state == 0) && !(playernum == 2 && n != 1 && state == 0))
	{
		if (playernum == 1)
			gr.update_ground(num - 1, -2);
		else if (playernum == 2)
			gr.update_ground(num - 1, -1);
	}
	if (state != 3)
	{
		system("cls");
		gr.show_ground(n);
		this->show_result(state);
	}
}
void player::show_result(int state)
{
	{
		SetColorAndBackground(6, 0);
		if (!are_connected)
			cout << "your opponent left the game.so..." << endl;

		if (state == playernum)
		{
			cout << "congrajulations! you wiiiiiiin!" << endl;
			the_end();
		}
		else if (state == 0)
		{
			cout << "Draw!" << endl;
			the_end();
		}
		else
		{
			cout << "Game over:(" << endl;
			the_end();
		}
		if (are_connected)
			after_game();
		else
			goodbye();
	}
}

void player::after_game()
{
	string choice;
	int flag = 0;
	thread t1(&player::receive_ans, this, ref(flag), ref(choice));
	thread t2(&player::send_ans, this, ref(flag), ref(choice));
	while (flag == 0);
	t1.detach();
	t1.~thread();
	t2.join();


}
void player::send_ans(int& flag, string& choice)
{
	string ans;
	SetColorAndBackground(2, 0);
	cout << "\n";
	cout << "1-Rematch" << endl << "2-Chat" << endl << "3-Exit" << endl;
	int x = correct_input(1, 3);

	if (flag == 0)
	{
		choice = to_string(x) + "\n";
		write(sock, boost::asio::buffer(choice));
		flag = 2;
		SetColorAndBackground(2, 0);
		if (x != 3)
			cout << "pending..." << endl;
		else
			goodbye();

	}
	if (flag == 1)
	{
		ans = to_string(x) + "\n";
		write(sock, boost::asio::buffer("NULL\n"));
		write(sock, boost::asio::buffer(ans));
	}
	if (flag == 2)//who fisrt sent a reqe
	{
		bool x = accept_or_reject();
		if (x == 1)
			ans = "1\n";
		else
			ans = "2\n";
	}

	if (ans == "1\n")
	{
		if (choice == "1\n")
			rematch();
		else if (choice == "2\n")
			chat();
		else goodbye();
	}
	else
		goodbye();




}
void player::receive_ans(int& flag, string& choice)
{
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	if (flag != 0)
		return;
	flag = 1;
	choice = buffer_cast<const char*>(buff.data());
	SetColorAndBackground(2, 0);
	if (choice == "1\n")
	{
		cout << "\nYour opponent wants to play again." << endl;
	}
	else if (choice == "2\n")
	{
		cout << "\nYour opponent wants to chat." << endl;
	}
	cout << "1-Accept" << endl << "2-Decline" << endl << "3-exit" << endl;
}
void player::rematch()
{
	//change playernum
	playernum = (playernum == 1) ? 2 : 1;

	//restart the game
	int i = start_game();
	ground g(i);
	g.show_ground(i);
	playgame(g, i);
}
void player::chat()
{
	SetColorAndBackground(2, 0);
	system("cls");
	cout << "__________________________________________________________" << endl;
	cout << "|                   Welcome to OX chat                   |" << endl;
	cout << "|________________________________________________________|" << endl;
	cout << "//Please enter 'EXIT' to exit the program" << endl << endl;
	thread t3(&player::sendTo, this);
	thread t4(&player::receiveFrom, this);

	t3.join();
	t4.join();

}
void player::receiveFrom()
{
	while (1) {
		boost::asio::streambuf buff;
		read_until(sock, buff, "\n");
		string s = buffer_cast<const char*>(buff.data());
		if (s == "EXIT\n")
			goodbye();
		SetColorAndBackground(9, 0);
		cout << s;
		SetColorAndBackground(14, 0);
	}
}
void player::sendTo()
{
	while (1) {
		string msg;
		SetColorAndBackground(14, 0);
		getline(cin, msg);
		msg += "\n";
		write(sock, boost::asio::buffer(msg));
		cout << endl;
		if (msg == "EXIT\n")
		{
			goodbye();
		}
	}
}

void player::goodbye()
{
	SetColorAndBackground(2, 0);
	cout << "felan khodahafezzzz" << endl;
	bye();
	exit(0);
}

//----------------------------------------------------------------------------------
//graphics
void player::calc(int i, int j)
{
	if (i == 26)
	{
		SetColorAndBackground(13, 0);
		return;
	}

	if (i == j || i == 9 + j || i == j + 18)
		SetColorAndBackground(13, 0);
	else
		SetColorAndBackground(8, 0);
}
void player::show_logo()
{

	Sleep(2000);
	for (int i = 0; i < 27; i++)
	{
		system("cls");
		calc(i, 0);
		cout <<
			"ooooooooooooooo\n";
		calc(i, 1);
		cout <<
			"o                    welocom to                     \n";
		calc(i, 2);
		cout <<
			"o                     _____  __                     \n";
		calc(i, 3);
		cout <<
			"o                    / _ \\ \\/ /                     \n";
		calc(i, 4);
		cout <<
			"o                   | | | \\  /                      \n";
		calc(i, 5);
		cout <<
			"o                   | |_| /  \\                    o\n";
		calc(i, 6);
		cout <<
			"o                    \\___/_/\\_\\                   o\n";
		calc(i, 7);
		cout <<
			"o                                                 o\n";
		calc(i, 8);
		cout <<
			"ooooooooooooooooooooooooooooooooooooooooooooooooooo\n";
		show_cow();
		Sleep(100);

	}
	hello();
	Sleep(600);
}
void player::show_cow()
{
	SetColorAndBackground(8, 0);
	cout <<
		"           O                                O\n"
		"              (      )        o   O                \n"
		"    o         ~(^^^^)~                             \n"
		"               ) ^^ \\~_          |\\                \n"
		"              /     | \\        \\~ /                \n"
		"             ( 0  0  ) \\        | |                \n"
		"              ---___/~  \\       | |                \n"
		"               /'__/ |   ~-_____/ |                \n"
		"o          _   ~----~      ___---~                 \n"
		"  O       //     |         |                       \n"
		"         ((~\\  _|         -|                       \n"
		"   o  O //-_ \\/ |        ~  |                      \n"
		"        ^   \\_ /         ~  |                      \n"
		"               |          ~ |                      \n"
		"               |     /     ~ |                     \n"
		"               |     (       |                     \n"
		"                \\     \\      /\\                    \n"
		"               / -_____-\\   \\ ~~-*                 \n"
		"               |  /       \\  \\       .==.          \n"
		"               / /         / /       |  |          \n"
		"             /~  |       /~  |       |__|          \n"
		"             ~~~~        ~~~~                      \n";

}