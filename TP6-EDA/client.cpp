#include "stdafx.h"
#include "client.h"
#include <iostream>

#define MSG_BUF 255

enum { ANIM, COUNT };

using namespace std;

client::client()
{
	IO_handler = new boost::asio::io_service();
	socket_forClient = new boost::asio::ip::tcp::socket(*IO_handler);
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
	cout << "Client created succesfully" << endl;
	error_flag = false;
	i_start = false;
	animation_seted = 0;
	bufC_len = 0;
}


client::~client()
{
	socket_forClient->close();
	delete client_resolver;
	delete socket_forClient;
	delete IO_handler;
}

void client::conect_to_host(const char * host, char* port_num)
{
	endpoint = client_resolver->resolve(
		boost::asio::ip::tcp::resolver::query(host, port_num));
	cout << "Trying to connect to " << host << " on port " << port_num << std::endl;
	boost::asio::connect(*socket_forClient, endpoint);
	socket_forClient->non_blocking(true);
}

void client::read_from_port()
{
	boost::system::error_code error;
	unsigned int len;
	cout << "Waiting message from server" << endl;
	do
	{
		len = socket_forClient->read_some(boost::asio::buffer(buf), error);

		if (!error)
			buf[len] = '\0';

	} while (error.value() == WSAEWOULDBLOCK);

	if (!error)
	{
		animation_seted = buf[ANIM];
		// hay que poner aca para que se fije si coincide la ip con la mia
		cout << "Server sais: " << buf << endl;
	}
	else
	{
		
		cout << "Error while trying to connect to server " << error.message() << endl;
	}
}

void client::send_msg(char* bufC)
{
	char buf_aux[MSG_BUF];
	int i = 0;
	while (bufC[i] != '\0') 
	{
		buf_aux[i] = bufC[i];
		i++;
	}
	buf_aux[i] = '\0';

	size_t len;
	boost::system::error_code error;

	do
	{
		len = socket_forClient->write_some(boost::asio::buffer(buf_aux, strlen(buf_aux)), error);
	} while ((error.value() == WSAEWOULDBLOCK));
	if (error)
		cout << "Error while trying to connect to server " << error.message() << endl;
}

bool client::read_error()
{
	return error_flag;
}

bool client::check_if_i_start()
{
	return i_start;
}

bool client::check_if_last()
{
	return ((buf[COUNT] + 2) == bufC_len) ? true : false;
}

char client::get_animation()
{
	return animation_seted;
}

void client::inc_counter()
{
	buf[COUNT]++;
}

char * client::get_buf()
{
	return buf;
}

