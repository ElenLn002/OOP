#ifndef LOADDOCUMENT_HPP
#define LOADDOCUMENT_HPP

#include "ISerialize.hpp"
#include "Document.hpp"

class LoadDocument {
public:
    void execute(std::string& filename, std::shared_ptr<Document> doc);
};

#endif //LOADDOCUMENT_HPP
