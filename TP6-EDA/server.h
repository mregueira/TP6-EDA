#include <boost/asio.hpp>

#define MSG_BUF 258


class server
{
public:
	server(unsigned int port_num);
	~server();
	void conect_to_port();
	void read_from_port();
	void send_msg(char *bufS);
	bool read_error();
	bool check_if_i_start();
	bool check_if_last();
	char get_animation();
	void set_bufSlen(unsigned int d);
	void close_serverAcceptor();
	void inc_counter();
	char* get_buf();
private:
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket_forServer;
	boost::asio::ip::tcp::acceptor* server_acceptor;

	char buf[MSG_BUF];
	unsigned int bufS_len;
	bool error_flag;
	bool i_start;
	char animation_seted;
};

