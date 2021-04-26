

#pragma once

#include <array>
#include <vector>
#include <algorithm>
namespace KTKR
{
    using byte = uint8_t;
    static_assert(sizeof(byte) == 1);
    struct AlignedChunk
    {
        struct Layout
        {
            std::vector<size_t> lengths;
            std::vector<size_t> offsets;
            size_t capacity;
        } layout;

        static Layout GenLayout(
            const std::vector<size_t> &alignments,
            const std::vector<size_t> &sizes) noexcept
        {
            const auto ALIGN_PACK = 8llu;
            Layout layout;
            const size_t SIZE = sizes.size();
            struct Item
            {
                size_t align;
                size_t idx;
                bool operator<(const Item &rhs) const noexcept
                {
                    return align < rhs.align;
                }
            };

            std::vector<Item> items(SIZE);
            for (size_t i = 0; i < SIZE; i++)
                items[i] = Item{alignments[i], i};
            // std::sort(items.begin(), items.end());
            size_t sumSize = 0;
            size_t longestSize = 0;
            for (size_t s : sizes)
            {
                sumSize += s;
                if (s > longestSize)
                    longestSize = s;
                layout.lengths.push_back(s);
            }

            layout.offsets.resize(SIZE);
            size_t curOffset = 0;
            for (size_t i = 0; i < SIZE; i++)
            {
                curOffset = items[i].align * ((curOffset + items[i].align - 1) / items[i].align);
                layout.offsets[items[i].idx] = curOffset;
                curOffset += sizes[items[i].idx];
            }
            layout.capacity = curOffset + sizes.back() + (std::min(ALIGN_PACK, longestSize)) - (curOffset + sizes.back()) % (std::min(ALIGN_PACK, longestSize));
            return layout;
        }

        AlignedChunk(const std::vector<size_t> &bufferIndex, size_t size)
        {
            _size = size;
            layout = GenLayout(bufferIndex, bufferIndex);
            buffer = new byte[_size * layout.capacity];
            for (size_t i = 0; i < _size * layout.capacity; i++)
                *(buffer + i) = 0;
        }
        ~AlignedChunk()
        {
            delete[] buffer;
        }
        bool IsValid() noexcept { return buffer != NULL; }
        byte *Data() noexcept { return buffer; }
        const size_t &size() noexcept { return _size; }
        template <typename T>
        T *GetPtr(size_t idx, size_t pos) noexcept
        {
            size_t ptr = idx * layout.capacity + layout.offsets[pos];
            return (T *)(buffer + ptr);
        }

    private:
        size_t _size;
        byte *buffer;
    };
} // namespace KTKR
