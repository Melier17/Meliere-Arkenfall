#include "Inventory.h"

#include <algorithm>

bool ItemStack::IsValid() const
{
    return !itemId.empty()
        && !displayName.empty()
        && quantity > 0
        && maxStack > 0
        && quantity <= maxStack;
}

Inventory::Inventory(int slotCapacity)
    : slotCapacity_(slotCapacity > 0 ? slotCapacity : 1)
{
}

int Inventory::GetCapacity() const
{
    return slotCapacity_;
}

int Inventory::GetUsedSlots() const
{
    return static_cast<int>(items_.size());
}

int Inventory::GetFreeSlots() const
{
    return slotCapacity_ - GetUsedSlots();
}

const std::vector<ItemStack>& Inventory::GetItems() const
{
    return items_;
}

int Inventory::GetRemainingCapacityFor(const std::string& itemId,
                                       int maxStack) const
{
    int remaining = 0;

    for (const ItemStack& stack : items_)
    {
        if (stack.itemId == itemId)
            remaining += stack.maxStack - stack.quantity;
    }

    remaining += GetFreeSlots() * maxStack;
    return remaining;
}

bool Inventory::AddItem(const std::string& itemId,
                        const std::string& displayName,
                        int quantity,
                        int maxStack)
{
    if (itemId.empty() || displayName.empty()
        || quantity <= 0 || maxStack <= 0)
        return false;

    if (GetRemainingCapacityFor(itemId, maxStack) < quantity)
        return false;

    int remaining = quantity;

    for (ItemStack& stack : items_)
    {
        if (stack.itemId != itemId || stack.maxStack != maxStack)
            continue;

        const int space = stack.maxStack - stack.quantity;
        const int amount = std::min(space, remaining);
        stack.quantity += amount;
        remaining -= amount;

        if (remaining == 0)
            return true;
    }

    while (remaining > 0 && GetFreeSlots() > 0)
    {
        const int amount = std::min(maxStack, remaining);
        items_.push_back({ itemId, displayName, amount, maxStack });
        remaining -= amount;
    }

    return remaining == 0;
}

bool Inventory::RemoveItem(const std::string& itemId, int quantity)
{
    if (itemId.empty() || quantity <= 0 || !HasItem(itemId, quantity))
        return false;

    int remaining = quantity;

    for (auto it = items_.begin(); it != items_.end() && remaining > 0; )
    {
        if (it->itemId != itemId)
        {
            ++it;
            continue;
        }

        const int amount = std::min(it->quantity, remaining);
        it->quantity -= amount;
        remaining -= amount;

        if (it->quantity == 0)
            it = items_.erase(it);
        else
            ++it;
    }

    return remaining == 0;
}

int Inventory::GetItemQuantity(const std::string& itemId) const
{
    int total = 0;

    for (const ItemStack& stack : items_)
    {
        if (stack.itemId == itemId)
            total += stack.quantity;
    }

    return total;
}

bool Inventory::HasItem(const std::string& itemId, int quantity) const
{
    return !itemId.empty() && quantity > 0
        && GetItemQuantity(itemId) >= quantity;
}

void Inventory::Clear()
{
    items_.clear();
}
