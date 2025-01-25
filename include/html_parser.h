#ifndef HTML_PARSER_H
#define HTML_PARSER_H

#include <string>
#include <vector>

class HtmlParser {
public:
    static std::vector<std::string> extractLinks(const std::string& htmlContent);
};

#endif
