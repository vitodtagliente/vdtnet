/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include <string>
#include <vector>

namespace net
{
	class string : public std::string
	{
	public:

		string();
		string(const std::string& str);

		enum class CompareMode
		{
			CaseSensitive,
			IgnoreCase
		};

		std::vector<string> split(const char delimiter) const;

		bool contains(const char match) const;
		bool contains(const std::string& match) const;

		bool startsWith(const std::string& match,
			const CompareMode mode = CompareMode::CaseSensitive) const;
		bool endsWith(const std::string& match,
			const CompareMode mode = CompareMode::CaseSensitive) const;

		string toLower() const;
		string toUpper() const;

		string trim() const;
		string trim(const char character) const;
		string ltrim() const;
		string ltrim(const char character) const;
		string rtrim() const;
		string rtrim(const char character) const;

		// retrieve all the string lines
		std::vector<string> getLines() const;
		string getFirstLine() const;
		
	};
}