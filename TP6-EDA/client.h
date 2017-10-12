#include <boost/asio.hpp>

#define MSG_BUF 258

class client
{
public:
	client();
	~client();
	void conect_to_host(const char* host, char* port_num);
	void read_from_port();
	void send_msg(char* bufC);
	bool read_error();
	bool check_if_i_start();
	bool check_if_last();
	char get_animation();
	void set_bufClen(unsigned int d);
	void inc_counter();
	char* get_buf();
private:
	boost::asio::io_service* IO_handler;
	boost::asio::ip::tcp::socket* socket_forClient;
	boost::asio::ip::tcp::resolver* client_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;
	char buf[MSG_BUF];
	unsigned int bufC_len;
	bool error_flag;
	bool i_start;
	char animation_seted;
};

