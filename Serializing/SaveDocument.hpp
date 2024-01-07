#ifndef SAVEDOCUMENT_HPP
#define SAVEDOCUMENT_HPP

#include <string>
#include <memory>

#include "ISerialize.hpp"
#include "Document.hpp"

class SaveDocument {
public:
    void execute(const std::string& filename, std::shared_ptr<Document> doc);

};

#endif //SAVEDOCUMENT_HPP
