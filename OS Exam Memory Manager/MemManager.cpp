#include <iostream>
#include <vector>
#include <bitset>
#include <optional>
#include <stdexcept>

struct PageDirectoryEntry {
    std::bitset<32> entry;

    PageDirectoryEntry() : entry(0) {}

    void setAddress(unsigned int address) {
        for (int i = 22; i < 32; ++i) {
            entry[i] = (address >> (31 - i)) & 1;
        }
    }

    void setPresent(bool present) {
        entry[0] = present;
    }

    void setReadWrite(bool readWrite) {
        entry[1] = readWrite;
    }

    void setUserSupervisor(bool userSupervisor) {
        entry[2] = userSupervisor;
    }
};

struct PageTableEntry {
    std::bitset<32> entry;

    PageTableEntry() : entry(0) {}

    void setAddress(unsigned int address) {
        for (int i = 12; i < 32; ++i) {
            entry[i] = (address >> (31 - i)) & 1;
        }
    }

    void setPresent(bool present) {
        entry[0] = present;
    }

    void setReadWrite(bool readWrite) {
        entry[1] = readWrite;
    }

    void setUserSupervisor(bool userSupervisor) {
        entry[2] = userSupervisor;
    }
};

class MemoryManager {
private:
    std::vector<unsigned char> physicalMemory;
    std::vector<PageTableEntry> pageTable;
    PageDirectoryEntry pageDirectory;
    size_t pageSize;

public:
    MemoryManager(size_t physicalMemorySize, size_t pageSize)
        : physicalMemory(physicalMemorySize), pageTable(physicalMemorySize / pageSize), pageSize(pageSize) {}

    unsigned int& operator[](size_t virtualAddress) {
        size_t pageIndex = (virtualAddress >> 22) & 0x3FF;
        size_t pageTableIndex = (virtualAddress >> 12) & 0x3FF;
        size_t offset = virtualAddress & 0xFFF;

        if (!pageDirectory.entry[pageIndex]) {
            throw std::invalid_argument("Page not present in Page Directory");
        }

        size_t frameNumber = extractFrameNumber(pageDirectory.entry.to_ulong());
        if (frameNumber >= pageTable.size()) {
            throw std::out_of_range("Frame number is out of range");
        }
        if (!pageTable[frameNumber].entry[pageTableIndex]) {
            throw std::invalid_argument("Page not present in Page Table");
        }

        size_t physicalAddress = (frameNumber << 12) | offset;
        return reinterpret_cast<unsigned int&>(physicalMemory[physicalAddress]);
    }

    void allocate(size_t virtualAddress) {
        size_t pageIndex = (virtualAddress >> 22) & 0x3FF;
        size_t pageTableIndex = (virtualAddress >> 12) & 0x3FF;
        size_t offset = virtualAddress & 0xFFF;

        auto frameNumberOpt = findFreeFrame();
        if (!frameNumberOpt.has_value()) {
            throw std::runtime_error("No free frames available");
        }
        size_t frameNumber = frameNumberOpt.value();

        if (!pageDirectory.entry[pageIndex]) {
            pageTable[frameNumber].entry.reset();
            pageTable[frameNumber].entry.set(0, true);
            pageTable[frameNumber].setAddress(frameNumber);
            pageDirectory.entry.set(pageIndex, true);
            pageDirectory.setAddress(static_cast<unsigned int>(frameNumber << 12));
        }

        if (!pageTable[frameNumber].entry[pageTableIndex]) {
            pageTable[frameNumber].entry.set(pageTableIndex, true);
            pageTable[frameNumber].setAddress(frameNumber);
        }
    }

    void deallocate(size_t virtualAddress) {
        size_t pageIndex = (virtualAddress >> 22) & 0x3FF;
        size_t pageTableIndex = (virtualAddress >> 12) & 0x3FF;

        if (!pageDirectory.entry[pageIndex]) {
            throw std::invalid_argument("Page not present in Page Directory");
        }

        size_t frameNumber = extractFrameNumber(pageDirectory.entry.to_ulong());
        if (!pageTable[frameNumber].entry[pageTableIndex]) {
            throw std::invalid_argument("Page not present in Page Table");
        }

        pageTable[extractFrameNumber(pageDirectory.entry.to_ulong())].entry.set(pageTableIndex, false);
    }

    std::optional<size_t> findFreeFrame() {
        for (size_t i = 0; i < pageTable.size(); ++i) {
            if (!pageTable[i].entry[0]) {
                return i;
            }
        }
        return std::nullopt;
    }

    unsigned int extractFrameNumber(unsigned int pageTableEntry) {
        return (pageTableEntry >> 12) & 0x3FF;
    }
};

int main() {
    size_t physicalMemorySize = 1 << 20; // Example: 1 MB of physical memory
    size_t pageSize = 1 << 12; // Example: Page size of 4 KB

    MemoryManager memoryManager(physicalMemorySize, pageSize);

    try {
        size_t virtualAddress = 0x00403000; // Example virtual address
        memoryManager.allocate(virtualAddress);
        std::cout << "Allocated page at virtual address: " << virtualAddress << std::endl;
        memoryManager[virtualAddress] = 21;

        unsigned int value = memoryManager[virtualAddress];
        std::cout << "Value at virtual address: " << value << std::endl;

        memoryManager.deallocate(virtualAddress);
        std::cout << "Deallocated page at virtual address: " << virtualAddress << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

