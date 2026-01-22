#include <iostream>
#include <libtorrent/bdecode.hpp>
#include <string>
#include <fstream>
int main()
{
	std::ifstream file("test.txt.torrent", std::ios::binary);
	if ( !file) 
	{
		std::cerr << "Failed to open file\n";
		return 1;
	}
	file.seekg(0, std::ios::end);
	std::size_t size = file.tellg();
	file.seekg(0, std::ios::beg);
	
	std::vector<char> buffer (size);
	file.read(buffer.data(), size);

	libtorrent::bdecode_node node;
	libtorrent::error_code ec;
	libtorrent::bdecode(buffer.data(), buffer.data() + buffer.size(), node, ec);
	if ( ec )
		std::cerr << ec.message() << "\n";
	else 
	{
		std::cout << libtorrent::print_entry(node);
	}
	std::cout << "Read " << buffer.size() << " bytes\n";
	return 0;
}
