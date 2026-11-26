#pragma once

#include <string>
#include <vector>

struct ItemStack
{
    std::string itemId;
    std::string displayName;
    int quantity = 0;
    int maxStack = 99;

    bool IsValid() const;
};

class Inventory
{
public:
    explicit Inventory(int slotCapacity = 20);

    int GetCapacity() const;
    int GetUsedSlots() const;
    int GetFreeSlots() const;
    const std::vector<ItemStack>& GetItems() const;

    bool AddItem(const std::string& itemId,
                 const std::string& displayName,
                 int quantity,
                 int maxStack = 99);

    bool RemoveItem(const std::string& itemId, int quantity);
    int GetItemQuantity(const std::string& itemId) const;
    bool HasItem(const std::string& itemId, int quantity = 1) const;
    void Clear();

private:
    int slotCapacity_;
    std::vector<ItemStack> items_;

    int GetRemainingCapacityFor(const std::string& itemId,
                                int maxStack) const;
};
