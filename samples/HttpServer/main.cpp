#include <iostream>
#include <vdtnet/net.h>

#include <vdtnet/internet/message.h>
#include <vdtnet/internet/serialization.h>

#include <vdtnet/http/http.h>

using namespace std;
using namespace net;

int main()
{
	net::startup();

	Address address("127.0.0.1:9090");
	
	internet::Message message;

	http::Request request;
	http::Response response;

	cout << message.toString();
	response = http::Response::parse(
R"(HTTP/1.1 200 OK
Date: Mon, 27 Jul 2009 12 : 28 : 53 GMT
Server: Apache/2.2.14 (Win32)
Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT
Content-Length: 88
Content-Type: text/html
Connection: Closed

<html>
<body>

<h1>Hello, World!</h1>

</body>
</html>)"
	);

	cout << response.toString();
	
	http::Server server(address, 20);
	if (server.listen())
	{
		cout << "Listening... " << address.toString() << endl;
	}

	net::shutdown();

	return 0;
}