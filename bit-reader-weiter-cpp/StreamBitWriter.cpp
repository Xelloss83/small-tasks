#include "StreamBitWriter.h"

namespace
{
	template <class T>
	void WriteArbitraryData(StreamBitWriter& stream, const T& val)
	{
		int number_of_bits = sizeof(T) * CHAR_BIT;

		while (--number_of_bits >= 0)
			stream << ((val & (1 << number_of_bits)) ? true : false);
	}
}


StreamBitWriter::StreamBitWriter(std::ostream& os)
	: m_stream(os.rdbuf())
	, m_count(sizeof(m_value) * CHAR_BIT)
{

}

StreamBitWriter::~StreamBitWriter()
{
}

std::streambuf* StreamBitWriter::Reset(std::ostream& os)
{
	return m_stream.rdbuf(os.rdbuf());
}

StreamBitWriter& StreamBitWriter::Flush(bool flush_not_finished, bool fill_not_finished_with)
{
	if (flush_not_finished && HasNotFinished())
	{
		for (int count = m_count; count > 0; --count)
			*this << fill_not_finished_with;
	}

	m_stream.flush();
	return *this;
}

bool StreamBitWriter::HasNotFinished() const
{
	return m_count < sizeof(m_value) * CHAR_BIT;
}

StreamBitWriter& StreamBitWriter::operator<<(bool bit)
{
	m_value |= (bit ? 1 : 0) << --m_count;

	if (m_count <= 0)
	{
		m_stream << m_value;
		m_value = 0;
		m_count = sizeof(m_value) * CHAR_BIT;
	}

	return *this;
}

StreamBitWriter& StreamBitWriter::operator<<(int val)
{
	WriteArbitraryData(*this, val);
	return *this;
}

StreamBitWriter& StreamBitWriter::operator<<(char val)
{
	WriteArbitraryData(*this, val);
	return *this;
}

StreamBitWriter& StreamBitWriter::operator<<(wchar_t val)
{
	WriteArbitraryData(*this, val);
	return *this;
}
