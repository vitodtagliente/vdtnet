#include <array>
#include <iostream>
#include <vdtnet/net.h>

using namespace std;
using namespace net;

void client_main();
void server_main();

#define SERVER_PORT 9670
#define CLIENT_PORT 9000

int main()
{
	net::startup();

	int choice = 0;
	cout << "UDP Chat [0: Server, 1: Client]: ";
	cin >> choice;

	if (choice == 0)
		server_main();
	else client_main();

	cout << "Premi un tasto per continuare...";

	net::shutdown();

	return 0;
}

void client_main()
{
	Socket socket(Address("127.0.0.1", CLIENT_PORT), Socket::TransportProtocol::UDP);
	if (socket.isValid())
	{
		if (socket.bind())
		{
			cout << "Socket binded successfully!" << endl;
			Address serverAddress("127.0.0.1", SERVER_PORT);
			// send hello
			{
				int32_t byteSent{ 0 };
				std::string data = "Hello server";
				socket.sendTo(serverAddress, (uint8_t*)data.c_str(), data.size(), byteSent);
			}
			// wait for the response
			{
				std::array<uint8_t, 100> buffer;
				const std::size_t buffer_size = buffer.max_size();
				int32_t byteRead{ 0 };
				while (socket.receiveFrom(serverAddress, &buffer[0], buffer_size, byteRead))
				{
					std::string data{ reinterpret_cast<char*>(&buffer[0]), static_cast<unsigned int>(byteRead) };
					cout << "Received message from server: " + data << endl;
				}
			}
		}
		else
		{
			cout << "Invalid socket binding" << endl;
		}
	}
	else
	{
		cout << "Invalid socket creation" << endl;
	}
}

void server_main()
{
	Socket socket(Address("127.0.0.1", SERVER_PORT), Socket::TransportProtocol::UDP);
	if (socket.isValid())
	{
		if (socket.bind())
		{
			cout << "Socket binded successfully!" << endl;
			cout << "Listening..." << endl;

			std::array<uint8_t, 100> buffer;
			net::Address clientAddress;
			const std::size_t buffer_size = buffer.max_size();
			int32_t byteRead{ 0 };
			while (socket.receiveFrom(clientAddress, &buffer[0], buffer_size, byteRead))
			{
				std::string data{ reinterpret_cast<char*>(&buffer[0]), static_cast<unsigned int>(byteRead) };
				cout << "Received message from client: " + data << endl;

				// send hello
				{
					int32_t byteSent{ 0 };
					std::string data = "Hello client";
					socket.sendTo(clientAddress, (uint8_t*)data.c_str(), data.size(), byteSent);
				}
			}
		}
		else
		{
			cout << "Invalid socket binding" << endl;
		}
	}
	else
	{
		cout << "Invalid socket creation" << endl;
	}
}