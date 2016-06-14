/*********************************************************************************************
* 
* ILS-Sim.org Server
* Copyright (C) 2016  ils-sim.org Team
* 
* This program is free software; you can redistribute it and/or modify it under the terms
* of the GNU General Public License as published by the Free Software Foundation; either
* version 3 of the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with this
* program; if not, see <http://www.gnu.org/licenses/>.
* 
*********************************************************************************************/

#include <string>
#include <sstream>

using namespace std;

#include "Http_Client.h"
#include "com_log/Log.h"

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

bool HttpClient::getHttpData(const string & server, const string & url, string & data)
{
	try
	{
		boost::asio::io_service io_service;
		std::stringstream data_stream;

		// Get a list of endpoints corresponding to the server name.
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(server, "http");
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		// Try each endpoint until we successfully establish a connection.
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		// Form the request. We specify the "Connection: close" header so that the
		// server will close the socket after transmitting the response. This will
		// allow us to treat all data up until the EOF as the content.
		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << "GET " << url << " HTTP/1.0\r\n";
		request_stream << "Host: " << server << "\r\n";
		request_stream << "Accept: */*\r\n";
		request_stream << "Connection: close\r\n\r\n";

		// Send the request.
		boost::asio::write(socket, request);

		// Read the response status line. The response streambuf will automatically
		// grow to accommodate the entire line. The growth may be limited by passing
		// a maximum size to the streambuf constructor.
		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		// Check that response is OK.
		std::istream response_stream(&response);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		std::getline(response_stream, status_message);
		if (!response_stream || http_version.substr(0, 5) != "HTTP/")
		{
			Log::GetInstance()->WriteWarning("HttpClient::getHttpData: Invalid response");
			return false;
		}
		if (status_code != 200)
		{
			Log::GetInstance()->WriteWarning("HttpClient::getHttpData: Response returned with status code " + status_code);
			return false;
		}

		// Read the response headers, which are terminated by a blank line.
		boost::asio::read_until(socket, response, "\r\n\r\n");

		// Process the response headers.
		std::string header;
		while (std::getline(response_stream, header) && header != "\r")
		{
			//std::cout << header << "\n";
		}
		//std::cout << "\n";

		// Write whatever content we already have to output.
		if (response.size() > 0)
		{
			data_stream << &response;
			//std::cout << &response;
		}

		// Read until EOF, writing data to output as we go.
		boost::system::error_code error;
		while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
		{
			data_stream << &response;
			//std::cout << &response;
		}
		if (error != boost::asio::error::eof)
		{
			throw boost::system::system_error(error);
		}
		data = data_stream.str();
	}
	catch (std::exception& e)
	{
		//std::cout << "Exception: " << e.what() << "\n";
		Log::GetInstance()->WriteWarning("HttpClient::getHttpData: Exception: " + string(e.what()));
		return false;
	}
	return true;
}

