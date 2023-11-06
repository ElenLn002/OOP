#ifndef DISPLAYEXECUTOR_HPP
#define DISPLAYEXECUTOR_HPP

class DisplayExecutor : public RenderingInterface {
public:
    DisplayExecutor(int ID, const std::map<int, std::string>& itemsMap);
    void execute(std::map<int, std::string>& itemsMap) override;

private:
    int itemID;
    const std::map<int, std::string>& itemsMap;
};


#endif //DISPLAYEXECUTOR_HPP
