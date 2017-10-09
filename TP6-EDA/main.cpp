// TP6EDA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "client.h"
#include "server.h"
#include <iostream>

#define DEF_PORT 12345
#define DEF_PORT_STR "12345"

using namespace std;

int main(int argc, char *argv[])
{

	if (argc > 2) {
		client c;
		c.conect_to_host("127.0.0.1", DEF_PORT_STR);
		cout << "Conected Succesful, press to send message" << endl;
		getchar();
		c.send_msg("TESTING");
		cout << "Message sended to server" << endl;
		do {
			c.read_from_port();
			if (!c.read_error()) {
				if (c.check_if_i_start()) {
					// pasar animacion
					c.inc_counter();
					if (c.check_if_last()) 
					{
						// pedir nueva secuencia
					}
				}
				cout << "Message received, Press to send message" << endl;
				getchar();
				c.send_msg(c.get_buf());
			}
		} while (true);
	}

	else {
		server s(DEF_PORT);
		s.conect_to_port();
		cout << "Conected Succesful" << endl;
		do
		{
			s.read_from_port();
			if (!s.read_error())
			{
				if (s.check_if_i_start()) {
					// pasar animacion
					s.inc_counter();
					if (s.check_if_last()) 
					{
						// pedir nueva secuencia
					}
				}
				cout << "Received OK, Press to send message" << endl;
				getchar();
				s.send_msg(s.get_buf());
			}

		} while (true);
	}

    return 0;
}

