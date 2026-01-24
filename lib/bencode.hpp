struct bstream {
	const uint8_t* curr;
	const uint8_t* end;
	uint8_t peek() { 
		if ( curr == end ) throw std::runtime_error("EOF");
		return *curr;
	}
	uint8_t next() { 
		if ( curr == end ) throw std::runtime_error("EOF"
		return *curr++; 
	}
	bstream(const std::vector<uint8_t>& bytes)
		: curr(bytes.data()), end(bytes.data() + bytes.size()){}
};
using decoded = std::variant<
	std::map<std::string, decoded>,
	std::vector<decoded>
	long,
	std::vector<uint8_t>
>;

class BEncode{
	constexpr uint8_t dict_start = 'd';
	constexpr uint8_t dict_end = 'e';
	constexpr uint8_t list_start = 'l';
	constexpr uint8_t list_end = 'e';
	constexpr uint8_t num_start = 'i';
	constexpr uint8_t num_end = 'e';
	constexpr uint8_t byte_array_divider = ':';

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

};
