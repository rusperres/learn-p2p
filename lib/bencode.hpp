struct bstream {
	const uint8_t* curr;
	const uint8_t* end;
	uint8_t peek() { return *curr;}
	uint8_t next() { return *curr++; }
	bstream(const auto& bytes){ curr = bytes.begin(), end = bytes.end();}
};
class BEncode{
	constexpr uint8_t dict_start = 'd';
	constexpr uint8_t dict_end = 'e';
	constexpr uint8_t list_start = 'l';
	constexpr uint8_t list_end = 'e';
	constexpr uint8_t num_start = 'i';
	constexpr uint8_t num_end = 'e';
	constexpr uint8_t byte_array_divider = ':';

	std::variant<std::orderered_set, std::vector, long int, std::vector<uint8_t>> decode(const auto& bytes){
		bstream enumerator = bstream(bytes);
		return decode_next_obj(enumerator);		
	}

	stdd::variant<std::orderered_set, std::vector, long int, std::vector<uint8_t> decode_next_obj(bstream enumerator){
		if ( it == end )
			throw std::runtime_error("Unexpected end of output");
		if( *it == dict_start) return decode_dict(enumerator);
		if( *it == list_start) return decode_list(enumerator);
		if( *it == num_start) return decode_num(enumerator);
		return decode_byte_array(enumerator);
	}

};
