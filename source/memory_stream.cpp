#include <vdtnet/memory_stream.h>

namespace net
{
	MemoryStream::MemoryStream() 
		: m_buffer() 
		, m_wordIndex()
	{}

	MemoryStream::MemoryStream(const std::size_t size) 
		: m_buffer(size)
		, m_wordIndex()
	{}

	MemoryStream::MemoryStream(const MemoryBuffer& buffer)
		: m_buffer(buffer) 
		, m_wordIndex()
	{}

	OutputMemoryStream::OutputMemoryStream()
		: MemoryStream(1) 
		, m_scratch()
		, m_offset()
	{}

	OutputMemoryStream::OutputMemoryStream(const std::size_t size) 
		: MemoryStream(size) 
		, m_scratch()
		, m_offset()
	{}

	void OutputMemoryStream::flush()
	{
		if (m_offset > 0)
		{
			assert(m_offset < bits_per_word);
			m_buffer[m_wordIndex] = uint32_t(m_scratch);
			m_scratch = m_offset = 0;
		}
	}

	InputMemoryStream::InputMemoryStream(const MemoryBuffer& buffer) 
		: MemoryStream(buffer)
		, m_scratch(m_buffer[m_wordIndex])
		, m_offset(bits_per_word)
	{}
}