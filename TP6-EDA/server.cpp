#include "stdafx.h"
#include "server.h"
#include <iostream>

enum {ANIM, COUNT};

using namespace std;

server::server(unsigned int port_num)
{
	IO_handler = new boost::asio::io_service();
	socket_forServer = new boost::asio::ip::tcp::socket(*IO_handler);
	server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
	boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port_num)); 
	std::cout << std::endl << "Ready. Port " << port_num << " created" << std::endl;
	error_flag = false;
	i_start = false;
	animation_seted = 0;
	bufS_len = 0;
}

server::~server()
{
	server_acceptor->close();
	socket_forServer->close();
	delete server_acceptor;
	delete socket_forServer;
	delete IO_handler;
}

void server::conect_to_port()
{
	server_acceptor->accept(*socket_forServer);
	socket_forServer->non_blocking(true);
}

void server::read_from_port()
{
	boost::system::error_code error;
	unsigned int len;
	cout << "Waiting message from client" << endl;
	do
	{
		len = (int) socket_forServer->read_some(boost::asio::buffer(buf), error);

		if (!error)
			buf[len] = '\0';
		bufS_len = len;

	} while (error.value() == WSAEWOULDBLOCK);

	if (!error) 
	{
		animation_seted = buf[ANIM];
		// hay que poner aca para que se fije si coincide la ip con la mia
		cout << "Client sais: " << buf << endl;
	}
	else 
	{
		error_flag = true;
		cout << "Error while trying to connect to client " << error.message() << endl;
	}
}

void server::send_msg(char * bufS)
{
	char buf_aux[MSG_BUF];
	int i = 0;
	while (bufS[i] != '\0')
	{
		buf_aux[i] = bufS[i];
		i++;
	}
	buf_aux[i] = '\0';

	size_t len;
	boost::system::error_code error;

	do
	{
		len = socket_forServer->write_some(boost::asio::buffer(buf_aux, strlen(buf_aux)), error);
	} while ((error.value() == WSAEWOULDBLOCK));
	if (error)
		cout << "Error while trying to connect to client " << error.message() << endl;
}

bool server::read_error()
{
	return error_flag;
}

bool server::check_if_i_start()
{
	return i_start;
}

bool server::check_if_last()
{
	return ((buf[COUNT] + 2) == bufS_len) ? true : false;
}

char server::get_animation()
{
	return animation_seted;
}

void server::inc_counter()
{
	buf[COUNT]++;
}

char * server::get_buf()
{
	return buf;
}
