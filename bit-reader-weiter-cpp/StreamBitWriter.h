#ifndef _STREAM_BIT_WRITER_H_
#define _STREAM_BIT_WRITER_H_

#include <ostream>

class StreamBitWriter
{
public:
	explicit StreamBitWriter(std::ostream& os);
	~StreamBitWriter();

	std::streambuf* Reset(std::ostream& os);
	StreamBitWriter& Flush(bool flush_not_finished = false, bool fill_not_finished_with = false);
	bool HasNotFinished() const;

	StreamBitWriter& operator<<(bool bit);
	StreamBitWriter& operator<<(int val);
	StreamBitWriter& operator<<(char val);
	StreamBitWriter& operator<<(wchar_t val);

private:
	std::ostream m_stream;
	char m_value = 0;
	short m_count = 0;
};

#endif //_STREAM_BIT_WRITER_H_