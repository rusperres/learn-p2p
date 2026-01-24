using byte_it = std::vector<uint8_t>::const_iterator;

class BEncode{
	constexpr uint8_t dict_start = 'd';
	constexpr uint8_t dict_end = 'e';
	constexpr uint8_t list_start = 'l';
	constexpr uint8_t list_end = 'e';
	constexpr uint8_t num_start = 'i';
	constexpr uint8_t num_end = 'e';
	constexpr uint8_t byte_array_divider = ':';

	std::any decode(const auto& bytes){
		auto it = bytes.begin();
		return decode_next_obj(it, bytes.end());		
	}

	std::any decode_next_obj(byte_it& it, byte_it end){
		if ( it == end )
			throw std::runtime_error("Unexpected end of output");
		if( *it == dict_start) return decode_dict(it, end);
		if( *it == list_start) return decode_list(it, end);
		if( *it == num_start) return decode_num(it, end);
		return decode_byte_array(it,end);
	}

};
