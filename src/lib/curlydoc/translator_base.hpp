#pragma once

#include <unordered_map>

#include <treeml/tree_ext.hpp>

namespace curlydoc{

class translator_base{
	const std::string file_name;
public:
	typedef std::function<void(bool, const treeml::tree_ext&)> keyword_handler_type;
	typedef std::function<void(const std::string&)> word_handler_type;
private:
	std::unordered_map<std::string, keyword_handler_type> handlers;

	void handle_char(const treeml::tree_ext& tree);
protected:
	void throw_syntax_error(std::string&& message, const treeml::tree_ext& node);

public:
	translator_base(std::string&& file_name);

	virtual ~translator_base(){}

	void translate(treeml::forest_ext::const_iterator begin, treeml::forest_ext::const_iterator end);

	void translate(const treeml::forest_ext& forest){
		this->translate(forest.begin(), forest.end());
	}

	void add_keyword(const std::string& keyword, keyword_handler_type&& handler);

	virtual void handle_space() = 0;
	virtual void handle_word(const std::string& word) = 0;
};

}
