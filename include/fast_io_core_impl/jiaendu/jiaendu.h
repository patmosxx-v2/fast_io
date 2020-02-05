#pragma once
#include"table_gen.h"

/*
Although it is still called jiaendu algorithm. The 64 bits are created by myself + I modified the table of jiaendu. It is no longer real jiaendu any more.
*/

namespace fast_io::details::jiaendu
{

template<std::unsigned_integral U,std::contiguous_iterator Iter>
inline std::size_t output_unsigned(U value,Iter str)
{
	using ch_type = std::remove_cvref_t<decltype(*str)>;
	constexpr std::size_t bytes4{4*sizeof(ch_type)};
	if constexpr(sizeof(U)==8)
	{
		if (value>=10000000000000000ULL)
		{
			std::uint64_t v4{value/10000000000000000ULL};
			std::uint64_t remains3{value-v4*10000000000000000ULL};
			std::uint64_t temp3(remains3/1000000000000ULL);
			std::uint64_t remains2
			{remains3-temp3*1000000000000ULL};
			remains3=temp3;
			std::uint64_t temp2{remains2};
			std::uint64_t remains0{remains2/10000};
			std::uint64_t remains1{remains2/100000000};
			remains2 = remains1;
			remains1 = remains0 - remains1*10000;
			remains0 = temp2 - remains0*10000;
			if (v4 >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[v4].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains3].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains2].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains1].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains0].data(),bytes4);
				return 20;
			}
			else
			{
				auto wstr(str);
				memcpy(wstr,static_tables<ch_type>::table5[v4].data(),bytes4);
				wstr += static_offset<>::offset[v4];
				memcpy(wstr,static_tables<ch_type>::table4[remains3].data(),bytes4);
				memcpy(wstr += 4,static_tables<ch_type>::table4[remains2].data(),bytes4);
				memcpy(wstr += 4,static_tables<ch_type>::table4[remains1].data(),bytes4);
				memcpy(wstr += 4,static_tables<ch_type>::table4[remains0].data(),bytes4);
				wstr += 4;
				return static_cast<std::size_t>(wstr-str);
			}
		}
		else if (value>=1000000000000ULL)
		{
			std::uint64_t v3{value/1000000000000ULL};
			std::uint64_t remains2
			{value-v3*1000000000000ULL};
			std::uint64_t temp2{remains2};
			std::uint64_t remains0{remains2/10000};
			std::uint64_t remains1{remains2/100000000};
			remains2 = remains1;
			remains1 = remains0 - remains1*10000;
			remains0 = temp2 - remains0*10000;
			if (v3 >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[v3].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains2].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains1].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains0].data(),bytes4);
				return 16;
			}
			else
			{
				auto wstr(str);
				memcpy(wstr,static_tables<ch_type>::table5[v3].data(),bytes4);
				wstr += static_offset<>::offset[v3];
				memcpy(wstr,static_tables<ch_type>::table4[remains2].data(),bytes4);
				memcpy(wstr += 4,static_tables<ch_type>::table4[remains1].data(),bytes4);
				memcpy(wstr += 4,static_tables<ch_type>::table4[remains0].data(),bytes4);
				wstr += 4;
				return static_cast<std::size_t>(wstr-str);
			}
		}
		else if (value >= 100000000)
		{
			std::uint64_t remains0{value/10000};// value/1,0000
			std::uint64_t remains1{value/100000000};// value/1,0000,0000
			auto v2(remains1);
			remains1 = remains0 - remains1*10000;
			remains0 = value - remains0*10000;
			if (v2 >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[v2].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains1].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains0].data(),bytes4);
				return 12;
			}
			else
			{
				auto wstr(str);
				memcpy(wstr,static_tables<ch_type>::table5[v2].data(),bytes4);
				wstr += static_offset<>::offset[v2];
				memcpy(wstr,static_tables<ch_type>::table4[remains1].data(),bytes4);
				memcpy(wstr += 4,static_tables<ch_type>::table4[remains0].data(),bytes4);
				wstr += 4;
				return static_cast<std::size_t>(wstr-str);
			}
		}
		else if (value >= 10000)
		{
			std::uint64_t const v2{
				(static_cast<std::uint64_t>(value) *
				static_cast<std::uint64_t>(3518437209)) >> 45};
			std::uint64_t const remains0{value - v2 * 10000};
			if (v2 >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[v2].data(),bytes4);
				str += 4;
				memcpy(str,static_tables<ch_type>::table4[remains0].data(),bytes4);
				return 8;
			}
			else
			{
				auto wstr(str);
				memcpy(wstr,static_tables<ch_type>::table5[v2].data(),bytes4);
				wstr += static_offset<>::offset[v2];
				memcpy(wstr,static_tables<ch_type>::table4[remains0].data(),bytes4);
				wstr += 4;
				return static_cast<std::size_t>(wstr - str);
			}
		}
		else
		{
			if (value >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[value].data(),bytes4);
				return 4;
			}
			else if (value >= 100)
			{
				memcpy(str,static_tables<ch_type>::table3[value].data(),3*sizeof(ch_type));
				return 3;
			}
			else if (value >= 10)
			{
				memcpy(str,static_tables<ch_type>::table2[value].data(),2*sizeof(ch_type));
				return 2;
			}
			else
			{
				*str = static_cast<ch_type>(static_cast<char8_t>(value)+u8'0');
				return 1;
			}
		}
	}
	else if constexpr(sizeof(U)==bytes4)
	{
		if (value >= 100000000)[[unlikely]]
		{
#if (_WIN64 || __x86_64__ || __ppc64__)
			std::uint64_t remains0{(static_cast<std::uint64_t>(value) *
			static_cast<std::uint64_t>(3518437209)) >> 45};
			std::uint64_t remains1{static_cast<std::uint64_t>(value) * 
			static_cast<std::uint64_t>((2882303762)) >> 58};
#else
			std::uint32_t remains0{value/10000};
			std::uint32_t remains1{value/100000000};
#endif
			auto v2(remains1);
			remains1 = remains0 - remains1*10000;
			remains0 = value - remains0*10000;
			if (v2 >= 10)
			{
				memcpy(str,static_tables<ch_type>::table5[v2].data(),2*sizeof(ch_type));
				memcpy(str += 2,static_tables<ch_type>::table4[remains1].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains0].data(),bytes4);
				return 10;
			}
			else
			{

				memcpy(++str,static_tables<ch_type>::table4[remains1].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains0].data(),bytes4);
				return 9;
			}
		}
		else if (value >= 10000)
		{
#if (_WIN64 || __x86_64__ || __ppc64__)
			std::uint64_t const v2{
				(static_cast<std::uint64_t>(value) *
				static_cast<std::uint64_t>(3518437209)) >> 45};
			std::uint64_t const remains0{value - v2 * 10000};
#else
			std::uint32_t const v2{value/10000};
			std::uint32_t const remains0{value - v2 * 10000};
#endif
			if (v2 >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[v2].data(),bytes4);
				str += 4;
				memcpy(str,static_tables<ch_type>::table4[remains0].data(),bytes4);
				return 8;
			}
			else
			{
				auto wstr(str);
				memcpy(wstr,static_tables<ch_type>::table5[v2].data(),bytes4);
				wstr += static_offset<>::offset[v2];
				memcpy(wstr,static_tables<ch_type>::table4[remains0].data(),bytes4);
				wstr += 4;
				return static_cast<std::size_t>(wstr - str);
			}
		}
		else
		{
			if (value >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[value].data(),bytes4);
				return 4;
			}
			else if (value >= 100)
			{
				memcpy(str,static_tables<ch_type>::table3[value].data(),3*sizeof(ch_type));
				return 3;
			}
			else if (value >= 10)
			{
				memcpy(str,static_tables<ch_type>::table2[value].data(),2*sizeof(ch_type));
				return 2;
			}
			else
			{
				*str = static_cast<char8_t>(value)+u8'0';
				return 1;
			}
		}
	}
	else if constexpr(sizeof(U)==2)
	{
		if (value >= 10000)
		{
#if (_WIN64 || __x86_64__ || __ppc64__)
			std::uint64_t const v2{
				(static_cast<std::uint64_t>(value) *
				static_cast<std::uint64_t>(3518437209)) >> 45};
			std::uint64_t const remains0{value - v2 * 10000};
#else
			std::uint32_t const v2{value/10000};
			std::uint32_t const remains0{value - v2 * 10000};
#endif
			if (v2 >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[v2].data(),bytes4);
				str += 4;
				memcpy(str,static_tables<ch_type>::table4[remains0].data(),bytes4);
				return 8;
			}
			else
			{
				auto wstr(str);
				memcpy(wstr,static_tables<ch_type>::table5[v2].data(),bytes4);
				wstr += static_offset<>::offset[v2];
				memcpy(wstr,static_tables<ch_type>::table4[remains0].data(),bytes4);
				wstr += 4;
				return static_cast<std::size_t>(wstr - str);
			}
		}
		else
		{
			if (value >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[value].data(),bytes4);
				return 4;
			}
			else if (value >= 100)
			{
				memcpy(str,static_tables<ch_type>::table3[value].data(),3*sizeof(ch_type));
				return 3;
			}
			else if (value >= 10)
			{
				memcpy(str,static_tables<ch_type>::table2[value].data(),2*sizeof(ch_type));
				return 2;
			}
			else
			{
				*str = static_cast<ch_type>(static_cast<char8_t>(value)+u8'0');
				return 1;
			}
		}
	}
	else if constexpr(sizeof(U)==1)
	{
		if (value >= 100)
		{
			memcpy(str,static_tables<ch_type>::table3[value].data(),3*sizeof(ch_type));
			return 3;
		}
		else if (value >= 10)
		{
			memcpy(str,static_tables<ch_type>::table2[value].data(),2*sizeof(ch_type));
			return 2;
		}
		else
		{
			*str = static_cast<char8_t>(value)+u8'0';
			return 1;
		}
	}
}
template<std::unsigned_integral U,std::contiguous_iterator Iter>
inline std::size_t output_unsigned_point(U value,Iter str)
{
	if(value >= 10)[[likely]]
	{
		std::size_t ret(output_unsigned(value,str+1));
		*str=str[1];
		str[1]=u8'.';
		return ret+1;
	}
	else
		return output_unsigned(value,str);
}

template<bool ln=false,bool sign=false,output_stream outp,std::unsigned_integral T>
inline void output(outp& out,T t)
{
	constexpr std::size_t reserved_size(32);
	if constexpr(buffer_output_stream<outp>)
	{
		auto reserved(oreserve(out,reserved_size));
		if constexpr(std::is_pointer_v<std::remove_cvref_t<decltype(reserved)>>)
		{
			if(reserved)[[likely]]
			{
				auto start(reserved-reserved_size);
				if constexpr(sign)
				{
					*start = u8'-';
					++start;
				}
				auto p(output_unsigned(t,start));
				if constexpr(ln)
				{
					start[p]=u8'\n';
					++p;
				}
				if constexpr(sign)
					orelease(out,(reserved_size-1)-p);
				else
					orelease(out,reserved_size-p);
				return;
			}
/*			std::size_t const ns(chars_len<10>(t));
			reserved = oreserve(out,ns);
			if(reserved)[[likely]]
			{
				auto start(reserved-ns);
				if constexpr(sign)
				{
					*start = u8'-';
					++start;
				}
				auto p(output_unsigned(t,start));
				if constexpr(ln)
				{
					start[p]=u8'\n';
					++p;
				}
				if constexpr(sign)
					orelease(out,(ns-1)-p);
				else
					orelease(out,ns-p);
				return;
			}*/
		}
		else
		{
			auto start(reserved-reserved_size);
			if constexpr(sign)
			{
				*start = u8'-';
				++start;
			}
			auto p(output_unsigned(t,std::to_address(start)));
			if constexpr(ln)
			{
				start[p]=u8'\n';
				++p;
			}
			if constexpr(sign)
				orelease(out,(reserved_size-1)-p);
			else
				orelease(out,reserved_size-p);
			return;
		}
	}
	std::array<typename outp::char_type,reserved_size> array;
	if constexpr(sign)
	{
		array.front() = u8'-';
		auto p(array.data()+1+output_unsigned(t,array.data()+1));
		if constexpr(ln)
		{
			*p=u8'\n';
			++p;
		}
		write(out,array.data(),p);
	}
	else
	{
		auto p(array.data()+output_unsigned(t,array.data()));
		if constexpr(ln)
		{
			*p=u8'\n';
			++p;
		}
		write(out,array.data(),p);
	}
}

}