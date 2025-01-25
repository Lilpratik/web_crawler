#include "html_parser.h"
#include <gumbo.h>

std::vector<std::string> HtmlParser::extractLinks(const std::string& htmlContent) {
    std::vector<std::string> links;

    GumboOutput* output = gumbo_parse(htmlContent.c_str());
    GumboVector* anchorTags = &output->root->v.element.children;

    for (size_t i = 0; i < anchorTags->length; ++i) {
        GumboNode* node = static_cast<GumboNode*>(anchorTags->data[i]);
        if (node->type == GUMBO_NODE_ELEMENT &&
            node->v.element.tag == GUMBO_TAG_A) {
            GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href");
            if (href) {
                links.push_back(href->value);
            }
        }
    }

    gumbo_destroy_output(&kGumboDefaultOptions, output);
    return links;
}
