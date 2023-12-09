#ifndef ISERIALIZER_HPP
#define ISERIALIZER_HPP

#include <map>
#include <string>
#include <memory>

#include "Document.hpp"

class ISerializer {
public:
    virtual void execute(const std::string& filename, std::shared_ptr<Document> doc) = 0;
};
#endif // ISERIALIZER_HPP
