#include <vdtnet/utils/string.h>

#include <algorithm>
#include <cctype>
#include <sstream>

namespace net
{
	string::string()
		: std::string()
	{

	}

	string::string(const std::string& str)
		: std::string(str)
	{

	}

	std::vector<string> string::split(const char delimiter) const
	{
		std::vector<string> tokens;
		string token;
		std::istringstream tokenStream(*this);
		while (std::getline(tokenStream, token, delimiter))
		{
			tokens.push_back(token);
		}
		return tokens;
	}

	bool string::contains(const char match) const
	{
		return find(match) != std::string::npos;
	}

	bool string::contains(const std::string& match) const
	{
		return find(match) != std::string::npos;
	}

	bool string::startsWith(const std::string& match,	const CompareMode mode) const
	{
		if (mode == CompareMode::CaseSensitive)
		{
			return find(match) == 0;
		}
		else
		{
			return toLower().find(string(match).toLower()) == 0;
		}
	}

	bool string::endsWith(const std::string& match, const CompareMode mode) const
	{
		return false;
	}

	string string::toLower() const
	{
		string result(*this);
		std::transform(result.begin(), result.end(), result.begin(), ::tolower);
		return result;
	}

	string string::toUpper() const
	{
		string result(*this);
		std::transform(result.begin(), result.end(), result.begin(), ::toupper);
		return result;
	}

	string string::trim() const
	{
		return rtrim().ltrim();
	}

	string string::trim(const char character) const
	{
		return rtrim(character).ltrim(character); 
	}

	string string::ltrim() const
	{
		string result(*this);
		auto it2 = std::find_if(
			result.begin(),
			result.end(),
			[](char ch)
			{ return !std::isspace(ch); }
		);
		result.erase(result.begin(), it2);
		return result;
	}

	string string::ltrim(const char character) const
	{
		string result(*this);
		auto it2 = std::find_if(
			result.begin(),
			result.end(),
			[character](char ch)
			{ return ch != character; }
		);
		result.erase(result.begin(), it2);
		return result;
	}

	string string::rtrim() const
	{
		string result(*this);
		auto it1 = std::find_if(
			result.rbegin(),
			result.rend(),
			[](char ch)
			{ return !std::isspace(ch); }
		);
		result.erase(it1.base(), result.end());
		return result;
	}

	string string::rtrim(const char character) const
	{
		string result(*this);
		auto it1 = std::find_if(
			result.rbegin(),
			result.rend(),
			[character](char ch)
			{ return ch != character; }
		);
		result.erase(it1.base(), result.end());
		return result;
	}

	std::vector<string> string::getLines() const
	{
		std::vector<string> lines;
		std::istringstream stream(*this);
		std::string line;
		while (std::getline(stream, line))
		{
			lines.push_back(line);
		}
		return lines;
	}
	
	string string::getFirstLine() const
	{
		std::istringstream stream(*this);
		std::string line;
		std::getline(stream, line);
		return line;
	}
}