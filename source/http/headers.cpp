#include <vdtnet/http/headers.h>

namespace net
{
	namespace http
	{
		bool Headers::contains(const std::string& field) const
		{
			return find(field) != end();
		}
	}
}