#ifndef _STREAM_BIT_READER_H_
#define _STREAM_BIT_READER_H_

#include <istream>

class StreamBitReader
{
public:
	explicit StreamBitReader(std::istream& is);
	~StreamBitReader();

	std::streambuf* Reset(std::istream& is);
	bool Eof() const;

	StreamBitReader& operator>>(bool& bit);
	StreamBitReader& operator>>(int& val);
	StreamBitReader& operator>>(char& val);
	StreamBitReader& operator>>(wchar_t& val);

	operator bool() const;

private:
	std::istream m_stream;
	char m_value = 0;
	short m_count = -1;
};

#endif //_STREAM_BIT_READER_H_
