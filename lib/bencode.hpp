struct bstream {
	const uint8_t* curr;
	const uint8_t* end;
	uint8_t peek() const { 
		if ( curr == end ) throw std::runtime_error("EOF");
		return *curr;
	}
	uint8_t next() { 
		if ( curr == end ) throw std::runtime_error("EOF")
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

	decoded decode(const std::vector<uint8_t>& bytes){
		bstream stream(bytes);
		return decode_next_obj(stream);		
	}

	decoded decode_next_obj(bstream& stream){
		if ( stream.curr == stream.end )
			throw std::runtime_error("Unexpected end of output");
		if( stream.peek() == dict_start) return decode_dict(stream.next());
		if( stream.peek() == list_start) return decode_list(stream.next());
		if( stream.peek() == num_start) return decode_num(stream.next());
		return decode_byte_array(stream);
	}

};
