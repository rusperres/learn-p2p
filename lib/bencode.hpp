#include <bits/stdc++.h>
struct bstream {
	const uint8_t* curr;
	const uint8_t* end;
	uint8_t peek() const { 
		if ( curr == end ) throw std::runtime_error("EOF");
		return *curr;
	}
	uint8_t next() { 
		if ( curr == end ) throw std::runtime_error("EOF");
		return *curr++; 
	}
	bstream(const std::vector<uint8_t>& bytes)
		: curr(bytes.data()), end(bytes.data() + bytes.size()){}
};
struct decoded;
using dict_t = std::map<std::string, decoded>;
using list_t = std::vector<decoded>;
struct decoded{
	using value_t = std::variant<
		dict_t,
		list_t,
		long,
		std::vector<uint8_t>
	>;

	value_t value;
};


class BEncode{
	static constexpr uint8_t dict_start = 'd';
	static constexpr uint8_t dict_end = 'e';
	static constexpr uint8_t list_start = 'l';
	static constexpr uint8_t list_end = 'e';
	static constexpr uint8_t num_start = 'i';
	static constexpr uint8_t num_end = 'e';
	static constexpr uint8_t byte_array_divider = ':';

	public:
	decoded decode(const std::vector<uint8_t>& bytes){
		bstream stream(bytes);
		return decode_next_obj(stream);		
	}

	decoded decode_next_obj(bstream& stream){
		if ( stream.curr == stream.end )
			throw std::runtime_error("Unexpected end of output");
		if( stream.peek() == dict_start) return decode_dict(stream);
		if( stream.peek() == list_start) return decode_list(stream);
		if( stream.peek() == num_start) return decode_num(stream);
		return decode_byte_array(stream);
	}
	
	decoded decode_file(std::string path){
		std::ifstream f(path, std::ios::binary);
		if ( !f ) 
			throw std::runtime_error("Error opening file: " + path);
		f.seekg(0, std::ios::end);
		std::size_t size = f.tellg();
		f.seekg(0, std::ios:beg);
		std::vector<uint8_t> bytes(size);
		f.read(reinterpret_cast<char*>(bytes.data()) ,size);
		return BEncode.decode(bytes);
	}

	decoded decode_number(bstream& stream){
		std::string num_bytes;
		while (	stream.next() ){
			if ( stream.current == num_end ) break;
			num_bytes += stream.curr();
		}

		return stoi(num_bytes);
		
	}

	decoded decode_byte_array(bstream& stream){
		std::vector<uint8_t> length_bytes;
		do {
			if ( stream.curr() == byte_array_divider) break;
			length_bytes.push_back(stream.curr());	
		} while ( stream.next() );
		
		std::string length_string(length_bytes.begin(), length_bytes.end());
		int length;
		try{
			length = std::stoi(length_string);
		} catch(...){
			throw std::runtime_error('Parsing integer failed.');
		}
		std::vector<uint8_t> bytes(length);
		for (int i = 0; i < length; i++){
			stream.next();
			bytes[i] = stream.curr();
		}
		return bytes;
	}
};
