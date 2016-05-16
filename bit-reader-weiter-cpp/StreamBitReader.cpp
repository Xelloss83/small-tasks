#include "StreamBitReader.h"


namespace
{
	template <class T>
	short ReadArbitraryData(StreamBitReader& stream, T& val)
	{
		int number_of_bits = sizeof(T) * CHAR_BIT;
		short number_of_bits_read = 0;
		bool bit;
		val = 0;

		while (--number_of_bits >= 0 && stream >> bit)
		{
			++number_of_bits_read;
			val |= ((bit ? 1 : 0) << number_of_bits);
		}

		return number_of_bits_read;
	}
}


StreamBitReader::StreamBitReader(std::istream& is)
	: m_stream(is.rdbuf())
{
}


StreamBitReader::~StreamBitReader()
{
}

std::streambuf* StreamBitReader::Reset(std::istream& is)
{
	return m_stream.rdbuf(is.rdbuf());
}

bool StreamBitReader::Eof() const
{
	return m_stream.eof();
}

StreamBitReader& StreamBitReader::operator>>(bool& bit)
{
	if (m_count <= 0)
	{
		m_count = sizeof(m_value) * CHAR_BIT;
		m_stream.get(m_value);
	}

	auto bit_mask = 1 << --m_count;

	bit = ((m_value & bit_mask) == bit_mask) ? true : false;

	return *this;
}

StreamBitReader& StreamBitReader::operator>>(int& val)
{
	ReadArbitraryData(*this, val);
	return *this;
}

StreamBitReader& StreamBitReader::operator>>(char& val)
{
	ReadArbitraryData(*this, val);
	return *this;
}

StreamBitReader& StreamBitReader::operator>>(wchar_t& val)
{
	ReadArbitraryData(*this, val);
	return *this;
}

StreamBitReader::operator bool() const
{
	return !Eof();
}
