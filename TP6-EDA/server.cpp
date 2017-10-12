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
	std::cout << std::endl << "--> Ok. Puerto " << port_num << " creado. Esperando conexion..." << std::endl;

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
	size_t len;
	cout << "--> Esperando mensaje de cliente..." << endl;
	do
	{
		len = socket_forServer->read_some(boost::asio::buffer(buf), error);

		if (!error) {
			buf[len] = '\0';
		}

	} while (error.value() == WSAEWOULDBLOCK);
	bufS_len = len;
	if (!error) 
	{
		animation_seted = buf[ANIM];
		
	}
	else 
	{
		error_flag = true;
		cout << "--> Error al intentar conectarse a cliente " << error.message() << endl;
	}
}

void server::send_msg(char * bufS)
{
	char buf_aux[MSG_BUF];
	unsigned int i = 0;
	while (i < bufS_len)
	{
		buf_aux[i] = bufS[i];
		i++;
	}
	buf_aux[i] = '\0';
	size_t len;
	boost::system::error_code error;

	do
	{
		len = socket_forServer->write_some(boost::asio::buffer(buf_aux, i), error);
	} while ((error.value() == WSAEWOULDBLOCK));
	if (error)
		cout << "--> Error al intentar conectarse a cliente " << error.message() << endl;
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

void server::set_bufSlen(unsigned int d)
{
	bufS_len = d;
}

void server::close_serverAcceptor()
{
	server_acceptor->close();
	socket_forServer->close();
}

void server::inc_counter()
{
	buf[COUNT]++;
}

char * server::get_buf()
{
	return buf;
}
